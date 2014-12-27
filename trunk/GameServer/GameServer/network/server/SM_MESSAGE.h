////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_MESSAGE_H_
#define _SM_MESSAGE_H_

void SM_MESSAGE(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeD(0);
	pck->writeD(0x001aa67f);
	pck->writeD(2);
	pck->writeD(0x44393238);
	pck->writeD(0x445259de);
	pck->writeD(0x41fc4bd0);
	pck->writeD(0x4438f340);
	pck->writeD(0x44518afd);
	pck->writeD(0x41f85aed);
	pck->PackSend(OPCODE_SM_MESSAGE);
}
/*
1003 0000
00000000
7FA61A00
02000000
38323944
DE595244
D04BFC41
40F33844
FD8A5144
ED5AF841                           ..QD.Z.A
*/
#endif

