////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////
#include "ai.h"

AI::AI(FILE* fg, DATABASE* mysql, ALL_PLAYERS* allplayers, MOB* mobs, int max_players, int max_spawns)
{
	this->fg = fg;
	this->mysql = mysql;
	this->players = allplayers;
	this->max_players = max_players;
	this->max_spawns = max_spawns;
	this->mobs = mobs;
}

AI::~AI()
{

}

void AI::SpawnObjects(int num_player)
{
	float dist;
	PACKET* pck = (PACKET*)players[num_player].pck;

	try {
		if (!pck->me->ingame)
			return;

		for (int i = 0; i < max_spawns; i++)
		{
			if (!mobs[i].accounts_show[num_player])
			{
				dist = sqrt((pck->me->pos_x - mobs[i].pos_x) * (pck->me->pos_x - mobs[i].pos_x) +
					(pck->me->pos_y - mobs[i].pos_y) * (pck->me->pos_y - mobs[i].pos_y) +
					(pck->me->pos_z - mobs[i].pos_z) * (pck->me->pos_z - mobs[i].pos_z));

				if (dist <= 60)
				{
					// spawn
					mobs[i].accounts_show[num_player] = true;
					SM_GAMEOBJECT_SPAWN(pck, mobs[i]);
				}
			}
			else
			{
				SM_OBJECT_MOVE(pck, mobs[i].uid, mobs[i].action_status,
					mobs[i].pos_x,
					mobs[i].pos_y,
					mobs[i].pos_z,
					mobs[i].next_pos_x,
					mobs[i].next_pos_y,
					mobs[i].next_pos_z);
			}
		}
	}
	catch (int ex)
	{

	}
}

//================================================================================
// Проверяет всех мобов и задает им действия
//
void AI::Obj_Actions()
{
	float dist;
	int rnd;

	for (int i = 0; i < max_spawns; i++)
	{
		switch (mobs[i].move)
		{
		case OBJMOVE_NOT_MOVE:
			break;

		case OBJMOVE_RANDOM:
			if (mobs[i].action_status == OBJ_ACTION_STAND || mobs[i].action_status == OBJ_ACTION_MOVE)
			{
				srand(GetTickCount());
				rnd = rand() % 100;
				if (rnd < 20)
				{
					srand(GetTickCount());
					mobs[i].action_status = OBJ_ACTION_MOVE;
					rnd = rand();
					if (rnd % 2)
					{
						srand(GetTickCount());
						rnd = rand() % mobs[i].move_distance;
						if (rnd % 3)
						{
							mobs[i].next_pos_x = mobs[i].base_pos_y + rnd;

						}
						else
						{
							mobs[i].next_pos_x = mobs[i].base_pos_y - rnd;

						}
					}
					srand(GetTickCount());
					rnd = rand();
					if (rnd % 2)
					{
						srand(GetTickCount());
						rnd = rand() % mobs[i].move_distance;
						if (rnd % 3)
						{
							mobs[i].next_pos_y = mobs[i].base_pos_y + rnd;

						}
						else
						{
							mobs[i].next_pos_y = mobs[i].base_pos_y - rnd;

						}
					}
				}
				else
				{
					mobs[i].action_status = OBJ_ACTION_STAND;
					mobs[i].pos_x = mobs[i].base_pos_x;
					mobs[i].pos_y = mobs[i].base_pos_y;
					mobs[i].pos_z = mobs[i].base_pos_z;
				}
//				_GET_DISTANCE(dist, mobs[i].pos_x, mobs[i].move_distance,
//									mobs[i].pos_y, mobs[i].move_distance,
//									mobs[i].pos_z, mobs[i].move_distance);


			}
			break;

		case OBJMOVE_POINTS:
			break;

		}
	}
}

//================================================================================
// Обработчик основного цикла нити
//
void AI::Frame()
{
	Obj_Actions();

	for (int num_player = 0; num_player < max_players; ++num_player)
		if (players[num_player].status == true && players[num_player].socket != NULL && players[num_player].pck != NULL)
		{
			EnterCriticalSection(&players[num_player].gCSp);

			StatusHandler(num_player);
			SpawnObjects(num_player);

			LeaveCriticalSection(&players[num_player].gCSp);
		}
}

//================================================================================
// Обработчик статусов игроков
//
void AI::StatusHandler(int num_player)
{
	PACKET* pck = (PACKET*)players[num_player].pck;

	switch (players[num_player].character.status)
	{
	case STATUS_NONE:
		break;

	case STATUS_CONNECT:
		lg::Info(fg, "GSNetwork [%s]: Connect character: %s\n", inet_ntoa(players[num_player].from), pck->me->tcharname);
		SM_UNK1(pck);
		SM_CONNECT(pck);
		break;

	case STATUS_SM_UNK3:
		SM_UNK3(pck, 0);
		SM_UNK3(pck, 12);
		SM_UNK3(pck, 19);
		SM_UNK3(pck, 15);
		SM_UNK3(pck, 12);
		SM_UNK3(pck, 11);
		SM_UNK4(pck);
		break;

	case STATUS_GETINFO:
/*//		pck->IsOnePacket(true);
		SM_CHARACTER_STATS(pck);
		SM_UNK20(pck);
		SM_UNK21(pck);
		SM_UNK24(pck);
//		SM_UNK25(pck);
//		SM_UNK26(pck);
//		SM_UNK27(pck);		
		
//		SM_UNK_1710(pck);
//		SM_SKILL_LIST(pck);
//		SM_SKILL_BUF(pck);
//		pck->IsOnePacket(false);*/
		break;
	}
	players[num_player].character.status = STATUS_NONE;
}