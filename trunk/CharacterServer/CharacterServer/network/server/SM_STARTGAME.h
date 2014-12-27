////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_STARTGAME_H_
#define _SM_STARTGAME_H_

void SM_STARTGAME(PACKET* pck, int character_id)
{
	//(h) hdddhhdd
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeD(0);
	pck->writeD(character_id);
	pck->writeD(inet_addr(gameserver_ip));		// ip gameserver
	pck->writeW(gameserver_port);				// port
	pck->writeW(1);								// zone
	pck->writeD(character_id);					// for gameserver
	pck->writeD(0);								// for gameserver
	pck->PackSend(OPCODE_SM_STARTGAME);
}

/*
1e00
0521
0000
00000000
19ef2500 - id character
70af5e1f - ip
71170000 - port
e2561300
e9c8f466

0500
0000
00000000
C7722700
70AF5E3A
7117
0100
E2561300
B44E49BD

*/
#endif


