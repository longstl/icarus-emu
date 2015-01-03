////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK25_H_
#define _SM_UNK25_H_

inline void SM_UNK25(PACKET* pck)
{
	// באפû
/*	pck->CreateBufForSend();
	pck->writeA("0000643D09800EBB000014CC3A44437627449E72D9410000B0420000000000000000643D0980000000000000000000000000FF47A43FFBFF090001000000FFFFFFFF0000000000000000F0804E3F010000000000000055005533FF55003000000000");
	pck->PackSend(OPCODE_SM_UNK25);

	pck->CreateBufForSend();
	pck->writeA("0000643D09800EBB00000100000001000000643D0980FF01070000000000");
	pck->PackSend(OPCODE_SM_UNK26);

	pck->CreateBufForSend();
	pck->writeA("000000000000643D0980643D09800EBB000000000000FBFF0900010000000000803F0000803F0100000030750000");
	pck->PackSend(OPCODE_SM_UNK27);

	pck->CreateBufForSend();
	pck->writeA("0000643D09800FBB000014CC3A44437627449E72D9410000B0420000000000000000643D0980000000000000000000000000FF0000003C000A0001000000FFFFFFFF0000000000000000F0804E3F010000000000000000000000FF00000007000000");
	pck->PackSend(OPCODE_SM_UNK25);

	pck->CreateBufForSend();
	pck->writeA("0000643D09800FBB05000100000001000000643D0980FF01070000000000");
	pck->PackSend(OPCODE_SM_UNK26);

	pck->CreateBufForSend();
	pck->writeA("000000000000643D0980643D09800FBB0000010000003C000A00010000000000803F0000803F0100000000000000");
	pck->PackSend(OPCODE_SM_UNK27);*/
	return;
	pck->writeW(0);
	pck->writeD(0x8004be84);
	pck->writeD(0x9e73);
	pck->writeD(0x443dd004);
	pck->writeD(0x44608e38);
	pck->writeD(0x42001d80);
	pck->writeD(0x420c0000);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(0x8004be84);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(0x403b06ff);
	pck->writeD(0x0009fffb);
	pck->writeD(1);
	pck->writeD(0xffffffff);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(0x3fe60790);
	pck->writeD(1);
	pck->writeD(0);
	pck->writeD(0x33550055);
	pck->writeD(0x300055ff);
	pck->writeD(0);
	pck->PackSend(OPCODE_SM_UNK25);
}

/*
18 00 00 00 06 33 02 80 0A EE 00 00 AB 7D 3E 44   . ...3.......}>D
83 B3 35 44 BD 6C B1 41 00 00 58 42 00 00 00 00   ..5D.l.A..XB....
00 00 00 00 06 33 02 80 00 00 00 00 00 00 00 00   .....3..........
00 00 00 00 FF 47 86 3F FB FF 09 00 01 00 00 00   .....G.?........
FF FF FF FF 00 00 00 00 00 00 00 00 F0 80 30 3F   ..............0?
01 00 00 00 00 00 00 00 55 00 55 33 FF 55 00 30   ........U.U3.U.0
00 00 00 00
*/

#endif

