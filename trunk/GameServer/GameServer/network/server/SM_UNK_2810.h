////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK_2810_H_
#define _SM_UNK_2810_H_

inline void SM_UNK_2810(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeD(pck->me->id);
	pck->writeD(0x00000200);
	pck->writeD(0x50f24401);
	pck->PackSend(OPCODE_SM_UNK_2810);
}

/*
1028 0000
91FE0D80
00200000
0144F250   .(....... ...D.P
*/

#endif

