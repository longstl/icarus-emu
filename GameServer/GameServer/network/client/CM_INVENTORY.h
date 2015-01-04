////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_INVENTORY_H_
#define _CM_INVENTORY_H_

inline void CM_INVENTORY(PACKET* pck)
{
	int16 unk1 = pck->readW();
	int8 unk2 = pck->readB();
	SM_INVENTORY_RESPONSE(pck);
}

/*



*/

#endif