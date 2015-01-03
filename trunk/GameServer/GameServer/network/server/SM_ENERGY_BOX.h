////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_ENERGY_BOX_H_
#define _SM_ENERGY_BOX_H_

inline void SM_ENERGY_BOX(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeA("00001DB50800CC810000B1D84E449ED654445A87C2410002030013460000000000000000000000000000FF20837400000000507F4336FF00000000000000");
	pck->PackSend(OPCODE_SM_ENERGY_BOX);
}

/*
18 1F 00 00 1D B5 08 00 CC 81 00 00 B1 D8 4E 44   ..............ND
9E D6 54 44 5A 87 C2 41 00 02 03 00 13 46 00 00   ..TDZ..A.....F..
00 00 00 00 00 00 00 00 00 00 00 00 FF 20 83 74   ............. .t
00 00 00 00 50 7F 43 36 FF 00 00 00 00 00 00 00   ....PC6........
*/

#endif

