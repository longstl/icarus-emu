////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_DISCONNECT_H_
#define _CM_DISCONNECT_H_

void CM_DISCONNECT(PACKET* pck)
{
	int16 unk1 = pck->readW();
	int8 unk2 = pck->readB();
	SM_DISCONNECT(pck);
}

/*
0EFA
0125
B0
*/

#endif