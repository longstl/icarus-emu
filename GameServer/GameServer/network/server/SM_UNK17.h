////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK17_H_
#define _SM_UNK17_H_

inline void SM_UNK17(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeD(0);
	pck->writeD(0x41180003);
	pck->writeD(0x00040183);
	pck->writeD(0x00040184);
	pck->writeD(0x00040188);
	pck->PackSend(OPCODE_SM_UNK17);
}

/*
0E00 0000
00000000
03000000
83010400
84010400
88010400
*/

#endif

