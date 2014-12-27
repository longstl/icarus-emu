////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_UNK2_H_
#define _CM_UNK2_H_

void CM_UNK2(PACKET* pck)
{
	int16 unk1 = pck->readW();
	int8 unk2 = pck->readB();
	SM_UNK3(pck, 0);
	SM_UNK3(pck, 12);
	SM_UNK3(pck, 19);
	SM_UNK3(pck, 15);
	SM_UNK3(pck, 12);
	SM_UNK3(pck, 11);
	SM_UNK4(pck);
}

/*

*/

#endif