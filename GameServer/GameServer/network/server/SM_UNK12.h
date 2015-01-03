////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK12_H_
#define _SM_UNK12_H_

inline void SM_UNK12(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeA("000000000000030A0000C77227000100000062000100010000000100000000000100C77227000200000063000100010000000100000001000700C772270003000000BD020000010000000100000002000300C77227000400000022000200010000000100000003000400C77227000500000036000600010000000000000004000000C7722700060000001C000800080000000000000005000100C77227000700000082020600030000000000000006000200C77227000900000081020600020000000000000007000300C77227000F00000000000400010000000000000008000400C77227000C0000007B000100010000000000000009000500");
	pck->PackSend(OPCODE_SM_CONNECT);
	return;
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