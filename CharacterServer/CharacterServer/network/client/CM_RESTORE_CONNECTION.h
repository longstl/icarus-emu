////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_RESTORE_CONNECTION_H_
#define _CM_RESTORE_CONNECTION_H_

void CM_RESTORE_CONNECTION(PACKET* pck)
{
	uint16 unk1 = pck->readW();
	uint32 account_id = pck->readD(); // 1356e2
	uint32 unk3 = pck->readD(); // 30
	uint32 unk4 = pck->readD(); // 6eddc0b0
	uint32 unk5 = pck->readD(); // d8
	SM_RESTORE_CONNECTION(pck);
}
/*
unk1 = 0x5502
unk2 = 0x1356e2
unk3 = 0x30
unk4 = 0x010001b0
unk5 = 0x01000001
*/
#endif