////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_UNK2_H_
#define _CM_UNK2_H_

void CM_UNK2(PACKET* pck)
{
	uint32 unk1 = pck->readW();
	uint32 unk2 = pck->readD();
	uint32 unk3 = pck->readD();
	SM_UNK1(pck);
}

/*
0e00
131e
0164
c0a1b389
590da021
*/

#endif

