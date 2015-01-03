////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_UNK28_H_
#define _CM_UNK28_H_

inline void CM_UNK28(PACKET* pck)
{
	int16 unk1 = pck->readW();
	int8 unk2 = pck->readB();
	
	SM_UNK_023e(pck);
	SM_UNK_033e(pck);
	SM_UNK28(pck);
}

/*

*/

#endif