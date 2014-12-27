////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////
#ifndef _LAUNCHER_SERVER_H_
#define _LAUNCHER_SERVER_H_

#include <config4cpp\Configuration.h>
#include "AI\ai.h"

using namespace config4cpp;

// Sockets
WORD				wVersionRequested;
WSADATA				wsaData;
SOCKET				s;
SOCKET				sock_accept;
sockaddr_in			from;
struct				sockaddr_in sin;
HANDLE				hpthr;
SETTINGS			settings;
CRITICAL_SECTION	gCS;
HANDLE				hConsole;

FILE*				fg;				// ����� ����� ��� ������

DATABASE*			mysql;			// �ܬݬѬ�� �լݬ� ��ѬҬ��� �� ����


//CHARACTERS_STRUCT*	char_structs;
ALL_PLAYERS*		allplayers;
AI*					server;

#endif _LAUNCHER_SERVER_H_