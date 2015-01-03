////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_UNK15_H_
#define _CM_UNK15_H_

inline void CM_UNK15(PACKET* pck)
{
	int16 unk1 = pck->readW();
	int8 unk2 = pck->readB();
	SM_UNK24(pck);
	SM_UNK25(pck);
//	SM_UNK26(pck);
//	SM_UNK27(pck);
}

/*



*/

#endif