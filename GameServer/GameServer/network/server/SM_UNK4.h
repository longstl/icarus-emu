////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK4_H_
#define _SM_UNK4_H_

void SM_UNK4(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeD(0);
	pck->writeD(0x01000101);
	pck->writeD(0x01000101);
	pck->writeD(0x01010101);
	pck->writeD(0x01000001);
	pck->writeD(0x00000101);
	pck->writeD(0x01000100);

	pck->PackSend(OPCODE_SM_UNK4);


}

/*
0E00
0000
00000000
01010001
01010001
01010101
01000001
01010000
00010001

*/

#endif

