////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_QUESTLIST_H_
#define _CM_QUESTLIST_H_

void CM_QUESTLIST(PACKET* pck)
{
	int16 unk1 = pck->readW();
	int8 unk2 = pck->readB();
	SM_QUESTLIST(pck);
}

/*



*/

#endif