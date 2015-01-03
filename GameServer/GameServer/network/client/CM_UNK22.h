////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_UNK22_H_
#define _CM_UNK22_H_

inline void CM_UNK22(PACKET* pck)
{
	int16 unk1 = pck->readW();
	int32 unk2 = pck->readD();
	SM_CHARACTER_STYLE(pck);
}

/*



*/

#endif