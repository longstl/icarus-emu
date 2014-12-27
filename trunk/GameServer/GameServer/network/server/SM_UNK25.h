////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK25_H_
#define _SM_UNK25_H_

void SM_UNK25(PACKET* pck)
{
	pck->CreateBufForSend();
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
1820
0000
84BE0480
739E0000
04D03D44
388E6044
801D0042
00000C42
00000000
00000000
84BE0480
00000000
00000000
00000000
FF063B40
FBFF0900
01000000
FFFFFFFF
00000000
00000000
9007E63F
01000000
00000000
55005533
FF550030
00000000
*/

#endif

