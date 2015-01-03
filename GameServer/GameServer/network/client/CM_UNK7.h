////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_UNK7_H_
#define _CM_UNK7_H_

inline void CM_UNK7(PACKET* pck)
{
	int16 unk1 = pck->readW();
	int8 unk2 = pck->readB();
	SM_UNK10(pck);
}

/*

0E 90 01 00 B2

*/

#endif