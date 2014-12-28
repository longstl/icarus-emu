////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////


#include "stdafx.h"
#include "defines.h"
#include "structs.h"
#include "common\logger.h"
#include "Settings.h"
#include "InnerServer.h"

#define PACKET_LEN	1024*64


void SendOK(uint8 id, SOCKET s)
{
	char packet_buf[3];
	packet_buf[0] = id;
	packet_buf[1] = 0x0a;
	send(s, packet_buf, 2, NULL);
}

DWORD WINAPI WinSockThread(LPVOID Param)
{
	bool connected = true;
	int packet_len;
	char packet_buf[PACKET_LEN];
	THREAD_SEND* stc = (THREAD_SEND*)Param;
	stc->id = -1;
	bool send_info = false;
	int step = 0;

	while (connected)
	{
		if ((packet_len = recv(stc->socket, packet_buf, PACKET_LEN, 0)) != -1)// 0)
		{
			switch (packet_buf[0])
			{
			case 1:
			{
				////////////////////////////////////////////////////////////////////////
				/// From login server
				////////////////////////////////////////////////////////////////////////
				switch (packet_buf[1])
				{
				case 0x11:
					log::Info(fg, "InnerThread: [%s] LoginServer connection.\n", inet_ntoa(stc->from));
					SendOK(stc->id, stc->socket);
					break;
				case 0x21:
					packet_buf[0] = 0x22;
					step = 0;
					for (int i = 0; i < 32; i++)
					{
						if (stc->gs_info[i].id != -1)
						{
							gs_info[i].cs_ip = cs_info[i].ip;
							gs_info[i].cs_port = cs_info[i].port;
							++step;
						}
					}

					packet_buf[1] = (uint8)step;
					step = 2;
					for (int i = 0; i < 32; i++)
					{
						if (stc->gs_info[i].id != -1)
						{
							memcpy(packet_buf + step, &gs_info[i], sizeof(GAMESERVER_INFO));
							step += sizeof(GAMESERVER_INFO);
						}
					}
					send(stc->socket, packet_buf, step, NULL);
					break;
				}
				break;
			}
			case 2:
			{
				////////////////////////////////////////////////////////////////////////
				/// From character server
				////////////////////////////////////////////////////////////////////////
				switch (packet_buf[1])
				{
				case 0x11:
					log::Info(fg, "InnerThread: [%s] Character Server (%d) connection.\n", inet_ntoa(stc->from), packet_buf[2]);
					stc->id = packet_buf[2];
					SendOK(stc->id, stc->socket);
					break;

				case 0x13:
					if (!send_info)
						log::Info(fg, "InnerThread: [%s] Character Server (%d) send info.\n", inet_ntoa(stc->from), stc->id);
					stc->cs_info[stc->id].id = stc->id;
					memcpy(&stc->cs_info[stc->id], packet_buf + 2, sizeof(CHARACTERSERVER_INFO));
					SendOK(stc->id, stc->socket);
					send_info = true;
					break;
				default:
					if (stc->id != -1)
						log::Info(fg, "InnerThread: [%s] Character Server (%d) Unknown package.\n", inet_ntoa(stc->from), stc->id);
					else
						log::Info(fg, "InnerThread: [%s] Character Server Unknown package.\n", inet_ntoa(stc->from));
					break;
				}
				break;
			}
			case 3:
			{
				////////////////////////////////////////////////////////////////////////
				/// From game server
				////////////////////////////////////////////////////////////////////////
				switch (packet_buf[1])
				{
				case 0x11:
					log::Info(fg, "InnerThread: [%s] Game Server (%d) connection.\n", inet_ntoa(stc->from), packet_buf[2]);
					stc->id = packet_buf[2];
					SendOK(stc->id, stc->socket);
					break;

				case 0x13:
					if (!send_info)
						log::Info(fg, "InnerThread: [%s] Game Server (%d) send info.\n", inet_ntoa(stc->from), stc->id);
					stc->gs_info[stc->id].id = stc->id;
					memcpy(&stc->gs_info[stc->id], packet_buf + 3, sizeof(GAMESERVER_INFO));
					SendOK(stc->id, stc->socket);
					send_info = true;
					break;

				default:
					if (stc->id != -1)
						log::Info(fg, "InnerThread: [%s] Game Server (%d) Unknown package.\n", inet_ntoa(stc->from), stc->id);
					else
						log::Info(fg, "InnerThread: [%s] Game Server Unknown package.\n", inet_ntoa(stc->from));
					break;

				}
				break;
			}
			default:
				log::Warn(fg, "InnerThread: [%s] Unknown connection.\n", inet_ntoa(stc->from));
				connected = false;
			}
		}
		Sleep(100);
	}
	
	if (stc->socket != NULL)
		closesocket(stc->socket);

	log::Info(fg, "InnerThread: [%s] Disconnect.\n", inet_ntoa(stc->from));

	delete(stc);
	return 0;
	
}


int _tmain(int argc, _TCHAR* argv[])
{
	int err;
	u_long iMode = 1;
	const char on = 1;
	InitializeCriticalSection(&gCS);

	for (int i = 0; i < 32; i++)
	{
		gs_info[i].id = -1;
		cs_info[i].id = -1;
	}

	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	fg = log::Init();
	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	log::Notify(fg, "\n");
	log::Notify(fg, "#################################\n");
	log::Notify(fg, "# Inner Server v1.00            #\n");
	log::Notify(fg, "# Author: Tahoma                #\n");
	log::Notify(fg, "#################################\n\n");

	///////////////////////////////////////////////////////////////
	// Загрузка конфигурации
	///////////////////////////////////////////////////////////////
	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	log::Notify(fg, "Load Settings... \t");

	if (!LoadSettings(&settings))
	{
		SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_RED | FOREGROUND_INTENSITY);
		log::Notify(fg, "Fail\n");
		return -1;
	}

	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	log::Notify(fg, "Succesful\n");
//--------------------------------------------------------------------------------------------------------------------------

	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	log::Notify(fg, "\nServer is running. (%s:%d)\n", ip, port);
	SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	err = ioctlsocket(s, FIONBIO, &iMode);

	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(ip);

	err = bind(s, (LPSOCKADDR)&sin, sizeof(sin));
	err = listen(s, SOMAXCONN);
	
	int fromlen;
	while (true)
	{
		fromlen = sizeof(from);
		sock_accept = accept(s, (struct sockaddr*)&from, &fromlen);
		if (sock_accept != INVALID_SOCKET)
		{
			THREAD_SEND* send = new THREAD_SEND;
			send->fg = fg;
			send->socket = sock_accept;
			send->from = from.sin_addr;
			send->gs_info = gs_info;
			send->cs_info = cs_info;
			send->hpthr = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)WinSockThread, send, NULL, NULL);
		}
		Sleep(100);
	}
	WSACleanup();

	settings.Destroy();
	return 0;
}

