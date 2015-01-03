////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK_0310_H_
#define _SM_UNK_0310_H_

inline void SM_UNK_0310(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeA("000000000000FFD03B0002000000F2AE3044741F25443E51BC41E56C2F44504E24443F51BC41");
	pck->PackSend(OPCODE_SM_UNK_0310);

	pck->CreateBufForSend();
	pck->writeA("000000000000DA1E78000200000022003144805A2E446C13DF41883E3144515E2C4430A9D641");
	pck->PackSend(OPCODE_SM_UNK_0310);

	pck->CreateBufForSend();
	pck->writeA("0000000000007E2178000200000046812F44E844304400C6DE41419C2B44994B2E449EA7D841");
	pck->PackSend(OPCODE_SM_UNK_0310);
	
	pck->CreateBufForSend();
	pck->writeA("00000000000095157B0002000000B87C3E4481F72B448781C0410D003E447B232844760AD441");
	pck->PackSend(OPCODE_SM_UNK_0310);	
	return;
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
	pck->PackSend(OPCODE_SM_UNK_0310);
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

