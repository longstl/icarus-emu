////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK32_H_
#define _SM_UNK32_H_

void SM_UNK32(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeD(0x5cc40001);
	pck->writeD(2);
	pck->writeD(0x0110);
	pck->writeD(1);
	pck->writeD(0x0c02022c);
	pck->writeD(0x0e0c);
	pck->writeD(0x010e);
	pck->writeD(1);
	pck->writeD(0x0c013538);
	pck->writeD(0x7f000e0c);
	pck->PackSend(OPCODE_SM_UNK32);
}

/*
3D03 0000
0100C45C
02000000
10010000
01000000
2C02020C
0C0E0000
0E010000
01000000
3835010C
0C0E007F
*/

#endif

