////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK12_H_
#define _SM_UNK12_H_

void SM_UNK12(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeD(0);
	pck->writeB(3);
	pck->writeW(4);
	pck->writeB(0);

	//for 
	pck->writeD(pck->me->id);
	pck->writeD(1);
	pck->writeW(0x62);
	pck->writeW(1);
	pck->writeD(1);
	pck->writeD(1);
	pck->writeW(0);
	pck->writeW(1);

	pck->writeD(pck->me->id);
	pck->writeD(2);
	pck->writeW(0x63);
	pck->writeW(1);
	pck->writeD(1);
	pck->writeD(1);
	pck->writeW(1);
	pck->writeW(7);

	pck->writeD(pck->me->id);
	pck->writeD(3);
	pck->writeW(0x02bd);
	pck->writeW(0);
	pck->writeD(1);
	pck->writeD(1);
	pck->writeW(2);
	pck->writeW(3);

	pck->writeD(pck->me->id);
	pck->writeD(4);
	pck->writeW(0x22);
	pck->writeW(2);
	pck->writeD(1);
	pck->writeD(1);
	pck->writeW(3);
	pck->writeW(4);
	pck->PackSend(OPCODE_SM_CONNECT);

}

/*
0E35
0000
00000000
03
0400
00
C7722700 - char id
01000000
6200
0100
01000000
01000000
0000
0100
C7722700 - char id
02000000
63000100
01000000
01000000
01000700
C7722700 - char id
03000000
BD020000
01000000
01000000
02000300
C7722700 - char id
04000000
22000200
01000000
01000000
03000400               ............


*/

#endif