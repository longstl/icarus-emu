////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK_3318_H_
#define _SM_UNK_3318_H_

inline void SM_UNK_3318(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeD(0x80023306);
	pck->writeD(0x0000ee0a);
	pck->PackSend(OPCODE_SM_UNK_3318);
}

/*
1833 0000 06330280 0AEE0000               .3...3......
*/

#endif

