////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_CONNECT_H_
#define _CM_CONNECT_H_

inline void CM_CONNECT(PACKET* pck)
{
	int16 unk1 = pck->readW();
	uint32 account_id = pck->readD();
	uint32 character_id = pck->readD();
	int16 unk4 = pck->readW();
	int16 unk5 = pck->readW();
	pck->sql->GetCharacterInfo(character_id, pck->me);
	pck->me->status = STATUS_CONNECT;
//	SM_UNK1(pck);
//	SM_CONNECT(pck);	
}

/*
0100
00000000
00000000
3000
b2d4


*/

#endif