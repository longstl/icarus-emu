////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_PING_H_
#define _CM_PING_H_

void CM_PING(PACKET* pck)
{
	uint8 unk2 = pck->readB();
	SM_PONG(pck, true);
}

#endif