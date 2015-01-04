////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_SKILL_PANEL_H_
#define _CM_SKILL_PANEL_H_

inline void CM_SKILL_PANEL(PACKET* pck)
{
	int16 unk1 = pck->readW();
	int8 unk2 = pck->readB();
//	SM_UNK_4b0e(pck);
	SM_SKILLS_PANEL(pck);
}

/*



*/

#endif