////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_QUESTLIST_H_
#define _SM_QUESTLIST_H_

void SM_QUESTLIST(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeD(0);
	pck->writeD(1);
	pck->writeD(0x6d);
	pck->writeD(0x00010000);
	pck->writeD(0x403b2b00);
	pck->writeD(0x01000001);
	pck->writeD(0);

	pck->PackSend(OPCODE_SM_QUESTLIST);


}

/*
0E3A
0000
00000000
01000000
6D000000
00000100
00021500
00000001
00000000

*/

#endif

