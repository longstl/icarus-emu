////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_UNK9_H_
#define _CM_UNK9_H_

void CM_UNK9(PACKET* pck)
{
	int16 unk1 = pck->readW();
	int8 unk2 = pck->readB();
	SM_UNK14(pck);
	SM_UNK15(pck);


}

/*



*/

#endif