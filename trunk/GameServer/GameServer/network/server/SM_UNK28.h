////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK28_H_
#define _SM_UNK28_H_

void SM_UNK28(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeD(0xb6);
	pck->writeD(0x3f800000);
	pck->writeD(0x3484e501);
	pck->PackSend(OPCODE_SM_UNK28);
}

/*
0F21 0000
B6000000
0000803F
01E58434
*/

#endif

