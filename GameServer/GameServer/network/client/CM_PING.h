////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_PING_H_
#define _CM_PING_H_

void CM_PING(PACKET* pck)
{
	time_t rawTime;
	time(&rawTime);
	pck->pingtime[0] = rawTime;
	int32 unk2 = pck->readD();
	SM_PONG(pck);
}

/*
0700 6501
00af00
*/

#endif