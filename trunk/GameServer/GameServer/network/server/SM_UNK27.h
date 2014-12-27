////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK27_H_
#define _SM_UNK27_H_

void SM_UNK27(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeD(0);
	pck->writeD(0x8004be84);
	pck->writeD(0x8004be84);
	pck->writeD(0x00009e73);
	pck->writeD(0x6e630100);
	pck->writeD(0x0009fffb);
	pck->writeD(1);
	pck->writeD(0x3f800000);
	pck->writeD(0x3f800000);
	pck->writeD(1);
	pck->writeD(0x00007530);
	pck->PackSend(OPCODE_SM_UNK27);
}

/*
1832 0000
00000000
84BE0480
84BE0480
739E0000
0001636E
FBFF0900
01000000
0000803F
0000803F
01000000
30750000
*/

#endif

