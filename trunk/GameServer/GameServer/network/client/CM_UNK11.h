////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_UNK11_H_
#define _CM_UNK11_H_

void CM_UNK11(PACKET* pck)
{
	int16 unk1 = pck->readW();
	int8 unk2 = pck->readB();
	SM_UNK17(pck);
	SM_ENTER_WORLD(pck);
	SM_UNK20(pck);
	SM_UNK21(pck);
	SM_GAMEOBJECT_SPAWN(pck);
}

/*



*/

#endif