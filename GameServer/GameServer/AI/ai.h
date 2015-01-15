////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////
#ifndef _AI_H_
#define _AI_H_

#include <Windows.h>
#include <stdio.h>
#include <winsock.h>
#include <assert.h>
#include <math.h>

#include "../common/mysql/mysql.h"
#include "../defines.h"
#include "../common/logger.h"
#include "../common/database.h"
#include "../structs.h"
#include "../game_structs.h"
#include "../network/packet.h"
#include "../network/opcodes.h"

using namespace OPCODES;

#define _GET_DISTANCE(out,px1,py1,pz1,px2,py2,pz2) out = sqrt((px1 - px2) * (px1 - px2) + (py1 - py2) * (py1 - py2) + (pz1 - pz2) * (pz1 - pz2));

class AI
{

public:
	AI(FILE* fg, DATABASE* mysql, ALL_PLAYERS* players, MOB* mobs, int max_players, int max_spawns);
	~AI();

	void Frame();												// Обработчик основного цикла нити
	void StatusHandler(int num_player);
	void SpawnObjects(int num_player);
	void Obj_Actions();											// Проверяет всех мобов и задает им действия

private:
	FILE*				fg;
	DATABASE*			mysql;
	MOB*				mobs;
	HANDLE				hpthr;									// хэндл основной нити
	int					max_players;
	int					max_spawns;
	ALL_PLAYERS*		players;
};


#endif _AI_H_


