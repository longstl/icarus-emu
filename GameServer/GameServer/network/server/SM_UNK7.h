////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK7_H_
#define _SM_UNK7_H_

// ������ �� �� � ������ �������
inline void SM_UNK7(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeA("00000000000000000000685A883F0100000000ED1F310100000001B3000000000000000000000000000000000000000000000000000000000000FEFFFFFFFFFFFFFF00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000003000A006D000000000000002000000000000000000000000000000001000000000000007F0000000000000093000000000000001C000000000000007E0000000000000089000000000000009400000000000000");
	pck->PackSend(OPCODE_SM_UNK7);
	return;
	pck->writeW(0);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(1);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(7);
	pck->writeD(0xbf800000);
	pck->writeD(1);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(1);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(7);
	pck->writeD(0);
	pck->writeD(0x00003218);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(1);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(7);
	pck->writeD(0x4ec60000);
	pck->writeD(1);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(1);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(7);
	pck->writeD(0x80040000);
	pck->writeD(0x00009e06);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(1);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(7);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(1);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(7);
	pck->writeD(0x16170000);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(3);

	pck->PackSend(OPCODE_SM_UNK7);


}

/*
0E3D
0000
00000000
00000000
00000000
00000000
01000000
00000000
00000000
07000000
000080BF
01000000 +
00000000
00000000
01000000
00000000
00000000
07000000
00000000
18320000
00000000
00000000
01000000
00000000
00000000
07000000+
0000C64E
01000000
00000000
00000000
01000000+
00000000
00000000
07000000+
00000480
069E0000+



00000000
00000000
01000000
00000000
00000000
07000000
00000000
00000000
00000000
00000000
01000000
00000000
00000000
07000000
00001716
00000000
00000000
00000000
03000000

*/

#endif

