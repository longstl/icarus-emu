////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////
#ifndef _AI_H_
#define _AI_H_

#include <Windows.h>
#include <stdio.h>
#include <winsock.h>
#include <assert.h>

#include "../common/mysql/mysql.h"
#include "../defines.h"
#include "../common/logger.h"
#include "../common/database.h"
#include "../structs.h"
#include "../game_structs.h"
#include "../network/packet.h"
#include "../network/opcodes.h"

using namespace OPCODES;

class AI
{

public:
	AI(FILE* fg, DATABASE* mysql, ALL_PLAYERS* players, int max_players);
	~AI();

	void Frame();												// ���������� ��������� ����� ����
	void StatusHandler(int num_player);

private:
	FILE*				fg;
	DATABASE*			mysql;
	HANDLE				hpthr;									// ����� �������� ����
	int					max_players;
	ALL_PLAYERS*		players;
};


#endif _AI_H_


