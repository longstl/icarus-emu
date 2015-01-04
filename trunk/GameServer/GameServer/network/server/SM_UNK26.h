////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK26_H_
#define _SM_UNK26_H_

inline void SM_UNK26(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeA("0000643D09800EBB00000100000001000000643D0980FF01070000000000");
	pck->PackSend(OPCODE_SM_UNK26);

	pck->CreateBufForSend();
	pck->writeA("0000643D09800FBB05000100000001000000643D0980FF01070000000000");
	pck->PackSend(OPCODE_SM_UNK26);
}

/*
0000
643D0980 - char id
0EBB0000
01000000
01000000
643D0980 - char id
FF010700
00000000
*/

#endif

