////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_CONNECT_H_
#define _CM_CONNECT_H_

void CM_CONNECT(PACKET* pck)
{
	int16 unk1 = pck->readW();
	uint32 character_id = pck->readD();
	int32 unk3 = pck->readD();
	int16 unk4 = pck->readW();
	int16 unk5 = pck->readW();
	pck->sql->GetCharacterInfo(character_id, pck->me);
	SM_UNK13(pck);
	SM_UNK1(pck);
	SM_CONNECT(pck);

}

/*
0100
00000000
00000000
3000
b2d4


*/

#endif