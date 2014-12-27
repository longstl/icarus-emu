////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_UNK1_H_
#define _CM_UNK1_H_

void CM_UNK1(PACKET* pck)
{
	uint32 unk1 = pck->readD();
	uint32 unk2 = pck->readD();
	SM_UNK1(pck);
}

/*
0204
051d
01030300
01010402
*/

#endif

