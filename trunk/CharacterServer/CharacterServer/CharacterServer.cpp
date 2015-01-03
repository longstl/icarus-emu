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


//====================================================================================
// ���� �������������� ������ �� ��������
//
DWORD WINAPI WinSockThread(LPVOID Param)
{
	EnterCriticalSection(&gCS);
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

	log::Info(fg, "CSNetwork [%s]: Disconnect (account id: %d)\n", inet_ntoa(account->from), account->account_id);
	
	EnterCriticalSection(&gCS);
	delete(th_struct->character);
	delete (pck);
	if (th_struct->socket != NULL)
		closesocket(th_struct->socket);

	free(th_struct);
	LeaveCriticalSection(&gCS);
	return 0;
}

//====================================================================================
// ���� �������������� ������ �� ���������������� ������
//
DWORD WINAPI InnerThread(LPVOID Param)
{
	int tmp = 0;
	int retVal = 0;
	char packet[256];
	LPHOSTENT hostEnt;
	CHARACTERSERVER_INFO c_info;

	c_info.id = gameserver_id;
	c_info.ip = inet_addr(accountserver_ip);
	c_info.port = accountserver_port;

	hostEnt = gethostbyname(inner_ip);
	SOCKET lsSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (lsSock == SOCKET_ERROR)
	{
		log::Error(fg, "InnerThread: Unable to create socket.\n");
		return false;
	}

	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = PF_INET;
	serverInfo.sin_addr = *((LPIN_ADDR)*hostEnt->h_addr_list);
	serverInfo.sin_port = htons(inner_port);
	retVal = connect(lsSock, (LPSOCKADDR)&serverInfo, sizeof(serverInfo));
	if (retVal == SOCKET_ERROR)
	{
		log::Error(fg, "InnerThread: Unable to connect\n");
		closesocket(lsSock);
		Sleep(5000);
		InnerThread(NULL);
		return false;
	}

	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	log::Info(fg, "InnerThread: Connected succesful.\n");

	uint16 opcode = 1;

	int status = 0;

	while (true)
	{
		switch (status)
		{
		case 0:
			packet[0] = 2;
			packet[1] = 0x11;
			packet[2] = c_info.id;
			retVal = send(lsSock, packet, 3, 0);
			if (retVal == SOCKET_ERROR) {
				log::Error(fg, "InnerThread: Disconnect.\n", WSAGetLastError());
				closesocket(lsSock);
				Sleep(5000);
				InnerThread(NULL);
				return 0;
			}
			else
			{
				log::Info(fg, "InnerThread: Connected.\n");
			}
			status = 1;
			break;

		case 1:
			packet[0] = 2;
			packet[1] = 0x13;
			//			memcpy(&packet[0], reinterpret_cast<uint8*>(&opcode), sizeof(opcode));
			memcpy(&packet[2], &c_info, sizeof(CHARACTERSERVER_INFO));

			retVal = send(lsSock, packet, sizeof(CHARACTERSERVER_INFO) + 2, 0);
			if (retVal == SOCKET_ERROR) {
				log::Error(fg, "InnerThread: Disconnect.\n", WSAGetLastError());
				closesocket(lsSock);
				Sleep(5000);
				InnerThread(NULL);
				return 0;
			}
			Sleep(2000 * 60);
			break;
		}
		Sleep(1000);
	}
	return 0;
}

//====================================================================================
// Main function
//
int _tmain(int argc, _TCHAR* argv[])
{
	int err;
	u_long iMode = 1;
	const char on = 1;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COLOR_GL
	fg = log::Init();
	log::Notify(fg, "\n");
	log::Notify(fg, "#################################\n");
	log::Notify(fg, "# Character Server v0.30        #\n");
	log::Notify(fg, "# Client version: 1.5.49        #\n");
	log::Notify(fg, "# Client time: 12:00 31.12.2014 #\n");
	log::Notify(fg, "#################################\n\n");

	///////////////////////////////////////////////////////////////
	// �������� ������
	///////////////////////////////////////////////////////////////
	COLOR_RGBL
	log::Notify(fg, "Load Settings... \t\t");

	setlocale(LC_ALL, "");
	Configuration* cfg = settings.Init();
	if (cfg == NULL)
	{
		COLOR_RL
		log::Notify(fg, "Fail\n");
		return -1;
	}

	gameserver_id = cfg->lookupInt("", "gameserver_id", 0);
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

	inner_ip = cfg->lookupString("", "inner_ip", "127.0.0.1");		// ip address inner
	inner_port = cfg->lookupInt("", "inner_port", 5600);			// inner port

	COLOR_GL
	log::Notify(fg, "Succesful\n");
	//-------------------------------------------------------------


	COLOR_RGBL
	log::Notify(fg, "Connect to Mysql... \t\t");
	mysql = new DATABASE(fg, (char*)db_host, (char*)db_user, (char*)db_pass, (char*)db_name);
	if (mysql->IsError())
	{
		COLOR_RL
		log::Notify(fg, "Fail\n");
		return -1;
	}

	COLOR_GL
	log::Notify(fg, "Succesful\n");

	COLOR_RGBL
	log::Notify(fg, "GameServer ID \t\t\t");
	COLOR_GL
	log::Notify(fg, "%d\n", gameserver_id);

	COLOR_GL
	log::Notify(fg, "\nServer is running. (%s:%d)\n", accountserver_ip, accountserver_port);
	COLOR_RGBL
	Sleep(500);

	InitializeCriticalSection(&gCS);

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	err = ioctlsocket(s, FIONBIO, &iMode);

	sin.sin_family = AF_INET;
	sin.sin_port = htons(accountserver_port);
	sin.sin_addr.s_addr = inet_addr(accountserver_ip);

	err = bind(s, (LPSOCKADDR)&sin, sizeof(sin));
	err = listen(s, SOMAXCONN);

	int fromlen;

	// ������ ����������� ������
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)InnerThread, NULL, NULL, NULL);

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

