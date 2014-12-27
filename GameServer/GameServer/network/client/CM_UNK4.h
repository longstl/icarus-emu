////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_UNK4_H_
#define _CM_UNK4_H_

void CM_UNK4(PACKET* pck)
{
	int16 unk1 = pck->readW();
	int8 unk2 = pck->readB();
	SM_UNK7(pck);
}

/*
*/

#endif