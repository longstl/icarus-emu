////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK32_H_
#define _SM_UNK32_H_

inline void SM_UNK32(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeA("010000000500000010010000010000002C02020C0C0E000005010000010000000F2617110C0E000012010000010000001D20031A0C0E000041010000010000002C2817110C0E00000E010000010000003835010C0C0E0000");
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

