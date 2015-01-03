////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////
#include "ai.h"

AI::AI(FILE* fg, DATABASE* mysql, ALL_PLAYERS* allplayers, int max_players)
{
	this->fg = fg;
	this->mysql = mysql;
	this->players = allplayers;
	this->max_players = max_players;
}

AI::~AI()
{

}

//================================================================================
// Обработчик основного цикла нити
//
void AI::Frame()
{
	for (int num_player = 0; num_player < max_players; ++num_player)
		if (players[num_player].status == true && players[num_player].socket != NULL)
		{
			EnterCriticalSection(&players[num_player].gCSp);

			StatusHandler(num_player);

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
		SM_UNK13(pck);
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
		pck->IsOnePacket(true);
		SM_ENTER_WORLD(pck);
		SM_UNK20(pck);
		SM_UNK21(pck);
		SM_UNK24(pck);
		SM_UNK25(pck);
		SM_UNK26(pck);
		SM_UNK27(pck);
		
//		SM_UNK_1710(pck);
//		SM_SKILL_LIST(pck);
//		SM_SKILL_BUF(pck);
		pck->IsOnePacket(false);
		break;
	}
	players[num_player].character.status = STATUS_NONE;
}