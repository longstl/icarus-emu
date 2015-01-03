////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_UNK14_H_
#define _CM_UNK14_H_

inline void CM_UNK14(PACKET* pck)
{
	int16 unk1 = pck->readW();
	int8 unk2 = pck->readB();
	SM_UNK32(pck);
	SM_SHIPS(pck);
	SM_ACHIEVEMENTS(pck);
}

/*



*/

#endif