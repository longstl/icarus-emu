////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_UNK_6e0e_H_
#define _CM_UNK_6e0e_H_

inline void CM_UNK_6e0e(PACKET* pck)
{
	int16 unk1 = pck->readW();
	int8 unk2 = pck->readB();
	SM_UNK_6f0e(pck);
}

/*

*/

#endif