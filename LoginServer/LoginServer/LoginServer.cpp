////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////
#include "stdafx.h"
#include "defines.h"
#include "common\database.h"
#include "structs.h"
#include "common\logger.h"
#include "Settings.h"
#include "LoginServer.h"

#include "network\packet.h"
#include "network\opcodes.h"

//====================================================================================
// Player connections
//
DWORD WINAPI WinSockThread(LPVOID Param)
{
	EnterCriticalSection(&gCS);
	THREAD_STRUCT* th_struct = (THREAD_STRUCT*)Param;
	PACKET* pck = new PACKET(th_struct);
	memset(pck->sockstruct->account_name, 0, sizeof(pck->sockstruct->account_name));
	LeaveCriticalSection(&gCS);

	while (pck->isconnected)
	{
		EnterCriticalSection(&gCS);
		if (pck->PackRecv())
			opcodes(pck);		
		LeaveCriticalSection(&gCS);
		Sleep(100);
	}
	
	if (strlen(pck->sockstruct->account_name) != 0)
		log::Info(fg, "Disconnect account: %s\n", pck->sockstruct->account_name);

	delete (pck);
	if (th_struct->socket != NULL)
		closesocket(th_struct->socket);

	delete(th_struct);
	return 0;
}

//====================================================================================
// Inner connections
//
DWORD WINAPI InnerConnection(LPVOID Param)
{
	int* param = (int*)Param;
	SOCKET sinner_accept = (SOCKET)param[0];
	int packet_len;
	char buf[PACKET_LEN];
	GAMESERVERS gs;
	memset(&gs, 0, sizeof(GAMESERVERS));

	while (true)	
	{
		if ((packet_len = recv(sinner_accept, buf, PACKET_LEN, 0)) == 0)
		{
//			log::Info(fg, "InnerLS: Disconnect [%s].\n", inet_ntoa(from_ls.sin_addr));
			closesocket(sinner_accept);
			return 0;
		}

		uint8 opcode = *(reinterpret_cast<uint8*>(&buf[0]));
		switch (opcode)
		{
			// информация о сервере
		case 1:
			memcpy(&gs, buf + 2, sizeof(GAMESERVERS));
			memcpy(&gameservers_info[gs.id-1], &gs, sizeof(GAMESERVERS));

			break;
		default:
		case 0:
			break;
		}
		Sleep(100);
	}

}
DWORD WINAPI InnerThread(LPVOID Param)
{
	int err;
	int fromlen;

	struct sockaddr_in sin_int;
	SOCKET sinner;
	SOCKET sinner_accept;
	sockaddr_in	from_ls;
	
	u_long iMode = 1;
	const char on = 1;

	sinner = socket(AF_INET, SOCK_STREAM, NULL);
	setsockopt(sinner, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	err = ioctlsocket(sinner, FIONBIO, &iMode);
	sin_int.sin_family = AF_INET;
	sin_int.sin_port = htons(inner_port);
	sin_int.sin_addr.s_addr = inet_addr(inner_ip);

	err = bind(sinner, (LPSOCKADDR)&sin_int, sizeof(sin_int));
	err = listen(sinner, SOMAXCONN);

	for (int i = 0; i < 12; i++)
	{
		gameservers_info[i].id = -1;
		gameservers_info[i].status = false;
	}

	while (true)
	{
		fromlen = sizeof(from_ls);
		sinner_accept = accept(sinner, (struct sockaddr*)&from_ls, &fromlen);
		if (sinner_accept != INVALID_SOCKET)
		{
			SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			log::Info(fg, "InnerLS: Connect [%s]\n", inet_ntoa(from_ls.sin_addr));

			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)InnerConnection, &sinner_accept, NULL, NULL);
		}
		Sleep(100);
	}

	return 0;
}


int _tmain(int argc, _TCHAR* argv[])
{
	int err;
	u_long iMode = 1;
	const char on = 1;
	sockaddr_in	from;
	SOCKET s;
	SOCKET sock_accept;
	struct sockaddr_in sin;

	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	fg = log::Init();

	log::Notify(fg, "\n");
	log::Notify(fg, "#################################\n");
	log::Notify(fg, "# Login Server v0.80            #\n");
	log::Notify(fg, "# Client version: 1.5.48        #\n");
	log::Notify(fg, "# Client time: 09:59 16.12.2014 #\n");
	log::Notify(fg, "#################################\n\n");

	///////////////////////////////////////////////////////////////
	// Load Settings
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
	db_name = cfg->lookupString("", "db_name", "ica_ls");
	launcher_ip = cfg->lookupString("", "ip", "127.0.0.1");			// ip address loginserver
	launcher_port = cfg->lookupInt("", "port", 5694);				// port loginserver
	inner_ip = cfg->lookupString("", "inner_ip", "127.0.0.1");		// ip address inner
	inner_port = cfg->lookupInt("", "inner_port", 5600);					// inner port

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

	Sleep(100);
	// inner server

	HANDLE hthInner = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)InnerThread, NULL, NULL, NULL);

	SetConsoleTextAttribute(hConsole, (WORD) FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	log::Notify(fg, "\nServer is running. (%s:%d)\n", launcher_ip, launcher_port);
	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	InitializeCriticalSection(&gCS);

	s = socket(AF_INET, SOCK_STREAM, NULL);	
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	err = ioctlsocket(s, FIONBIO, &iMode);

	sin.sin_family = AF_INET;
	sin.sin_port = htons(launcher_port);
	sin.sin_addr.s_addr = inet_addr(launcher_ip);

	err = bind(s, (LPSOCKADDR)&sin, sizeof(sin));
	err = listen(s, SOMAXCONN);

	int fromlen;

	while (true)
	{	

		fromlen = sizeof(from);
		sock_accept = accept(s, (struct sockaddr*)&from, &fromlen);
		if (sock_accept != INVALID_SOCKET)
		{
			THREAD_STRUCT* th_struct = new THREAD_STRUCT;
			th_struct->socket = sock_accept;
			th_struct->fg = fg;
			th_struct->mysql = mysql;
			th_struct->gameservers_info = gameservers_info;
			th_struct->hpthr = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)WinSockThread, th_struct, NULL, &th_struct->thrSocketRead);
		}

		Sleep(100);
	}
	WSACleanup();

	return 0;
}

