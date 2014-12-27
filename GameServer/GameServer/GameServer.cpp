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
#include "GameServer.h"

#include "network\packet.h"
#include "network\opcodes.h"

#include "AI\ai.h"


DWORD WINAPI WinSockThread(LPVOID Param)
{
	
	THREAD_SEND* send = (THREAD_SEND*)Param;
	send->player->pck = new PACKET(send->player->socket, &send->player->character, (DATABASE*)send->sys.mysql, send->sys.fg, &send->player->ping_time);
	PACKET* pck = (PACKET*)send->player->pck;
	log::Info(fg, "Connect: %s\n", inet_ntoa(send->player->from));
	pck->me->id = 0;
	InitializeCriticalSection(&send->player->gCSp);

	while (pck->isconndected)
	{
		EnterCriticalSection(&send->player->gCSp);
		
		if (pck->PackRecv())
		{
			do
			{
				if ((uint16)pck->packet_len == 0)
				{
					pck->isconndected = false;
					break;
				}				

				/*
				// DEBUG
				char bindbg[2];
				memset(bindbg, 0, 2);

				char* fordebug = pck->GetPacketPointer();
				log::Debug(fg, "C->S: op[%04x][%02x] ", pck->opcode, pck->real_packet_size);
				for (uint16 i = 0; i < (uint16)pck->packet_len; i++)
				{
					if ((uint8)fordebug[i] > 0x20 && (uint8)fordebug[i] <= 'z')
					{
						bindbg[0] = (uint8)fordebug[i]; 
						log::Notify(fg, bindbg);
					}
					else
						log::Notify(fg, ".");
				}
				log::Notify(fg, "\n");

				log::Debug(fg, "C->S: op[%04x][%02x] ", pck->opcode, pck->real_packet_size);
				for (uint16 i = 0; i < (uint16)pck->packet_len; i++)
					log::Notify(fg, "%02x", (uint8)fordebug[i]);

				log::Notify(fg, "\n");
				// --DEBUG
				*/
				opcodes(pck);
			} while (pck->NextPacket());
		}		
		LeaveCriticalSection(&send->player->gCSp);
		Sleep(100);
	}
	
	delete (pck);
	if (send->player->socket != NULL)
		closesocket(send->player->socket);

	send->player->status = false;
	delete(send);
	return 0;
	
}


DWORD WINAPI WinSockPing(LPVOID Param)
{
	ALL_PLAYERS* players = (ALL_PLAYERS*)Param;
	while (true)
	{
		for (int i = 0; i < max_players; i++)
		{
			if (players[i].status == true && players[i].socket != NULL)
			{
				EnterCriticalSection(&players[i].gCSp);

				PACKET* pck = (PACKET*)players[i].pck;
				SM_PONG(pck);
				time_t rawTime;
				time(&rawTime);
				int time = rawTime - players[i].ping_time;
				if (time > 0 && time > max_time_for_disconnect)
				{
					pck->Disconnect();
					log::Warn(fg, "PingThread: Сlient does not respond. Character: %s\n", pck->me->charname);
				}	
				
				LeaveCriticalSection(&players[i].gCSp);
			}
		}
		Sleep(2500);
	}
}

DWORD WINAPI InnerLS(LPVOID Param)
{
	int tmp = 0;
	int retVal = 0;
	char packet[256];
	LPHOSTENT hostEnt;
	GAMESERVER_INFO	g_info;

	memset(g_info.name, 0, 42);	
	strcpy(g_info.name, name_server);

	hostEnt = gethostbyname(inner_ls_ip);
	SOCKET lsSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (lsSock == SOCKET_ERROR)
	{
		log::Error(fg, "InnerLS: Unable to create socket.\n");
		return false;
	}

	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = PF_INET;
	serverInfo.sin_addr = *((LPIN_ADDR)*hostEnt->h_addr_list);
	serverInfo.sin_port = htons(inner_ls_port);
	retVal = connect(lsSock, (LPSOCKADDR)&serverInfo, sizeof(serverInfo));
	if (retVal == SOCKET_ERROR)
	{
		log::Error(fg, "InnerLS: Unable to connect\n");
		closesocket(lsSock);
		Sleep(5000);
		InnerLS(NULL);
		return false;
	}

	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	log::Info(fg, "InnerLS: Connected succesful.\n");

	uint16 opcode = 1;

	while (true)
	{
		time_t rawTime;
		time(&rawTime);

		tmp = 0;
		g_info.id = (uint8)id_server;

		for (int i = 0; i < max_players; i++)
		{
			if (allplayers[i].status)
				++tmp;
		}

		g_info.players_connected = tmp;
		g_info.players_max = max_players;
		g_info.status = technical_works;
		g_info.timeupdate = rawTime;
		g_info.cs_ip = inet_addr(cs_ip);
		g_info.cs_port = cs_port;

		memcpy(&packet[0], reinterpret_cast<uint8*>(&opcode), sizeof(opcode));
		memcpy(&packet[2], &g_info, sizeof(GAMESERVER_INFO));

		retVal = send(lsSock, packet, sizeof(GAMESERVER_INFO)+2, 0);
		if (retVal == SOCKET_ERROR) {
			log::Error(fg, "InnerLS: Disconnect.\n", WSAGetLastError());
			closesocket(lsSock);
			Sleep(5000);
			InnerLS(NULL);
			return 0;
		}
		Sleep(refresh_server_info);
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int err;
	u_long iMode = 1;
	const char on = 1;
	InitializeCriticalSection(&gCS);

	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	fg = log::Init();
	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	log::Notify(fg, "\n");
	log::Notify(fg, "#################################\n");
	log::Notify(fg, "# Game Server v0.01             #\n");
	log::Notify(fg, "# Client version: 1.5.48        #\n");
	log::Notify(fg, "# Client time: 09:59 16.12.2014 #\n");
	log::Notify(fg, "#################################\n\n");

	///////////////////////////////////////////////////////////////
	// Загрузка конфигурации
	///////////////////////////////////////////////////////////////
	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	log::Notify(fg, "Load Settings... \t\t");

	if (!LoadSettings(&settings))
	{
		SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_RED | FOREGROUND_INTENSITY);
		log::Notify(fg, "Fail\n");
		return -1;
	}

	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	log::Notify(fg, "Succesful\n");
//--------------------------------------------------------------------------------------------------------------------------

	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	log::Notify(fg, "Connect to Mysql... \t\t");
	mysql = new DATABASE(fg, (char*)db_host, (char*)db_user, (char*)db_pass, (char*)db_name);
	if (mysql->IsError())
		return -1;

	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	log::Notify(fg, "Succesful\n");

	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	log::Notify(fg, "Max players... \t\t\t");
	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	log::Notify(fg, "%d\n", max_players);
	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	log::Notify(fg, "ID server... \t\t\t");
	if (id_server > 12)
	{
		SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_RED | FOREGROUND_INTENSITY);
		log::Notify(fg, "Fail\n");
		return -1;
	}
	else
	{
		SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		log::Notify(fg, "%d\n", id_server);
	}

	allplayers = new ALL_PLAYERS[max_players];
	for (int i = 0; i < max_players; i++)
	{
		allplayers[i].status = false;
		allplayers[i].socket = NULL;
	}

	///////////////////////////////////////////////////////////////
	// Загрузка информации для сервера
	///////////////////////////////////////////////////////////////


	server = new AI();

	// Запуск слежения за состояниями соединений игроков
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)WinSockPing, allplayers, NULL, NULL);
//--------------------------------------------------------------------------------------------------------------------------

	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	log::Notify(fg, "\nServer is running. (%s:%d)\n", gameserver_ip, gameserver_port);
	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	err = ioctlsocket(s, FIONBIO, &iMode);

	sin.sin_family = AF_INET;
	sin.sin_port = htons(gameserver_port);
	sin.sin_addr.s_addr = inet_addr(gameserver_ip);

	err = bind(s, (LPSOCKADDR)&sin, sizeof(sin));
	err = listen(s, SOMAXCONN);
	
	// Запуск внутреннего обмена с LS
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)InnerLS, NULL, NULL, NULL);

	int fromlen;
	while (true)
	{
		fromlen = sizeof(from);
		sock_accept = accept(s, (struct sockaddr*)&from, &fromlen);
		if (sock_accept != INVALID_SOCKET)
			for (int i = 0; i < max_players; i++)
				if (allplayers[i].status == false)
				{
					THREAD_SEND* send = new THREAD_SEND;
					send->sys.fg = fg;
					send->sys.mysql = mysql;

					send->player = &allplayers[i];
					send->player->status = true;
					send->player->from = from.sin_addr;
					send->player->socket = sock_accept;
					send->player->hpthr = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)WinSockThread, send, NULL, NULL);
					break;
				}
		Sleep(100);
	}
	WSACleanup();

	settings.Destroy();
	delete(allplayers);
	return 0;
}

