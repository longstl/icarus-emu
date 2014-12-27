////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////


#include "stdafx.h"
#include "defines.h"
#include "game_structs.h"
#include "common\database.h"
#include "structs.h"
#include "common\logger.h"
#include "Settings.h"
#include "CharacterServer.h"

#include "network\packet.h"
#include "network\opcodes.h"


DWORD WINAPI WinSockThread(LPVOID Param)
{
	EnterCriticalSection(&gCS);
	CHARACTER* tmp_char;
	THREAD_STRUCT* th_struct = (THREAD_STRUCT*)Param;
	PACKET* pck = new PACKET(th_struct);
	th_struct->character = new CHARACTER[max_characters+1];
	for (int i = 0; i < max_characters; i++)
		th_struct->character[i].id = 0;

	memset(th_struct->pin_code, 0, 5);
	th_struct->status = STATUS_NONE;
	th_struct->pin_erros = 0;

	LeaveCriticalSection(&gCS);

	while (pck->isconndecred)
	{
		EnterCriticalSection(&gCS);

		if (pck->PackRecv())
			opcodes(pck);
		LeaveCriticalSection(&gCS);
		Sleep(100);
	}
	
	EnterCriticalSection(&gCS);
	delete(th_struct->character);
	delete (pck);
	if (th_struct->socket != NULL)
		closesocket(th_struct->socket);

	free(th_struct);
	LeaveCriticalSection(&gCS);
	return 0;
}




int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	fg = log::Init();
	log::Notify(fg, "\n");
	log::Notify(fg, "#################################\n");
	log::Notify(fg, "# Character Server v0.30        #\n");
	log::Notify(fg, "# Client version: 1.5.48        #\n");
	log::Notify(fg, "# Client time: 09:59 16.12.2014 #\n");
	log::Notify(fg, "#################################\n\n");

	///////////////////////////////////////////////////////////////
	// zagruzka configuracii
	///////////////////////////////////////////////////////////////
	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	log::Notify(fg, "Load Settings... \t\t");

	setlocale(LC_ALL, "");
	Configuration* cfg = settings.Init();
	if (cfg == NULL)
	{
		SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_RED | FOREGROUND_INTENSITY);
		log::Notify(fg, "Fail\n");
		return -1;
	}

	db_host = cfg->lookupString("", "db_host", "127.0.0.1");
	db_user = cfg->lookupString("", "db_user", "root");
	db_pass = cfg->lookupString("", "db_pass", "password");
	db_name = cfg->lookupString("", "db_name", "ica_gs");
	accountserver_ip = cfg->lookupString("", "ip", "127.0.0.1");			// ip adres accounserver
	accountserver_port = cfg->lookupInt("", "port", 5965);					// port accountserver
	gameserver_ip = cfg->lookupString("", "gameserver_ip", "127.0.0.1");	// ip adres gameserver
	gameserver_port = cfg->lookupInt("", "gameserver_port", 6001);			// port gameserver
	max_characters = cfg->lookupInt("", "max_characters", 5);				// max characters 
	int use_pincode = cfg->lookupInt("", "use_pincode", 0);
	if (use_pincode == 1)
		use_pin_code = true;
	else
		use_pin_code = false;

	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	log::Notify(fg, "Succesful\n");
	//-------------------------------------------------------------


	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	log::Notify(fg, "Connect to Mysql... \t\t");
	mysql = new DATABASE(fg, (char*)db_host, (char*)db_user, (char*)db_pass, (char*)db_name);
	if (mysql->IsError())
	{
		SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_RED | FOREGROUND_INTENSITY);
		log::Notify(fg, "Fail\n");
		return -1;
	}

	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	log::Notify(fg, "Succesful\n");

	SetConsoleTextAttribute(hConsole, (WORD) FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	log::Notify(fg, "\nServer is running. (%s:%d)\n\n\n", accountserver_ip, accountserver_port);
	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	InitializeCriticalSection(&gCS);

	int err;
	u_long iMode = 1;
	const char on = 1;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	err = ioctlsocket(s, FIONBIO, &iMode);

	sin.sin_family = AF_INET;
	sin.sin_port = htons(accountserver_port);
	sin.sin_addr.s_addr = inet_addr(accountserver_ip);

	err = bind(s, (LPSOCKADDR)&sin, sizeof(sin));
	err = listen(s, SOMAXCONN);

	int fromlen;

	while (true)
	{			
		fromlen = sizeof(from);
		sock_accept = accept(s, (struct sockaddr*)&from, &fromlen);
		if (sock_accept != INVALID_SOCKET)
		{
			THREAD_STRUCT* th_struct = (THREAD_STRUCT*)malloc(sizeof(THREAD_STRUCT));// new THREAD_STRUCT;
			th_struct->from = from.sin_addr;
			th_struct->socket = sock_accept;
			th_struct->fg = fg;
			th_struct->mysql = mysql;
			th_struct->hpthr = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)WinSockThread, th_struct, NULL, &th_struct->thrSocketRead);
		}

		Sleep(100);
	}
	WSACleanup();

	settings.Destroy();
	return 0;
}

