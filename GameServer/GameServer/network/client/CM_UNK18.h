////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_UNK18_H_
#define _CM_UNK18_H_

inline void CM_UNK18(PACKET* pck)
{
	int16 unk1 = pck->readW();
	int8 unk2 = pck->readB();
	SM_SKILL_LIST(pck);
}

/*



*/

#endif