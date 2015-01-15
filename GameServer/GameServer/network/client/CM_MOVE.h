////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_MOVE_H_
#define _CM_MOVE_H_

inline void CM_MOVE(PACKET* pck)
{
	int8  unk2 = pck->readB();		// 0 - идти / 1 - бежать
	int8 status = pck->readB();
	int8 unk3 = pck->readB();
	int8 unk4 = pck->readB();
	int32 unk5 = pck->readD();
	float p1_x = pck->readF();		// 759.582
	float p1_y = pck->readF();		// 898.307861
	float p1_z = pck->readF();		// 32.02
	float p2_x = pck->readF();		// 765.3179
	float p2_y = pck->readF();		// 890.116333
	float p2_z = pck->readF();		// 32.02
	int32 unk12 = pck->readD();		// -2
	int32 unk13 = pck->readD();

	if (status == 1)
		pck->me->action = ACTION_MOVE;
	else
		pck->me->action = ACTION_NONE;

	pck->me->pos_x = p1_x;
	pck->me->pos_y = p1_y;
	pck->me->pos_z = p1_z;
	pck->me->next_x = p2_x;
	pck->me->next_y = p2_y;
	pck->me->next_z = p2_z;
}

/*
start:
0190
01			
01				- status
00
5a
0d000000
42e53d44		- pos_x
b4936044		- pos_Y
2e1c0042		- pos_z
59543f44		- to pos_x
72875e44		- to pos_y
2e1c0042		- to pos_z
70f721c0		
00006b22

stop:
0190
01
00				- status
00
38
0d000000
59eb3d44		- pos_x
018b6044		- pos_Y
fcffff41		- pos_z
59eb3d44		- to pos_x
018b6044		- to pos_y
fcffff41		- to pos_z
70f721c0
00006b22
*/

#endif