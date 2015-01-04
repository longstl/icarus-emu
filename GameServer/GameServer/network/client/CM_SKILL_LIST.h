////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_SKILL_LIST_H_
#define _CM_SKILL_LIST_H_

inline void CM_SKILL_LIST(PACKET* pck)
{
	int16 unk1 = pck->readW();
	int8 unk2 = pck->readB();
	SM_SKILL_LIST(pck);
}

/*



*/

#endif