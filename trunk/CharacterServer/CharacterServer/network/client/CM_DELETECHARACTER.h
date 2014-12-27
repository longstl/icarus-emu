////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_DELETECHARACTER_H_
#define _CM_DELETECHARACTER_H_

void CM_DELETECHARACTER(PACKET* pck)
{
	Sleep(1500);
	int16 unk1 = pck->readW();	// 0x0b02
	int32 character_id = pck->readD();
	int32 unk2 = pck->readD();	// 0x40d36979
	int32 unk3 = pck->readD();	// 0x3dc88415
	int32 unk4 = pck->readD();	// 0xbee4fc27

	account->status = STATUS_DELETE_CHARACTER;
	if (use_pin_code)
	{
		SM_GETPIN(pck, character_id);
	}
	else
	{
		SM_DELETECHARACTER(pck, character_id);
	}
}

#endif