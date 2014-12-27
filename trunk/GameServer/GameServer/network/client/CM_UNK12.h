////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_UNK12_H_
#define _CM_UNK12_H_

void CM_UNK12(PACKET* pck)
{
	int16 unk1 = pck->readW();
	int8 unk2 = pck->readB();
	SM_UNK18(pck);
}

/*



*/

#endif