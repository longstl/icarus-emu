////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_CHAT_H_
#define _CM_CHAT_H_

void CM_CHAT(PACKET* pck)
{	
	int8 cryptflag = pck->readB();
	int8 unk1 = pck->readB();

	uint32 unk2 = pck->readD();
	uint32 unk3 = pck->readD();
	uint32 unk4 = pck->readD();
	uint32 unk5 = pck->readD();
	uint32 unk6 = pck->readD();
	uint32 unk7 = pck->readD();
	uint32 unk8 = pck->readD();
	uint32 unk9 = pck->readD();
	uint32 unk10 = pck->readD();
	uint32 unk11 = pck->readD();
	uint32 unk12 = pck->readD();

	//	SM_UNK1(pck);
}

/*
01dd
016d
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
0400 - num symbols
31323334 - str
c1a1


*/

#endif