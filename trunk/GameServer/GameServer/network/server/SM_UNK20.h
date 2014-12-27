////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK20_H_
#define _SM_UNK20_H_

void SM_UNK20(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeD(0x403b2b00);
	pck->PackSend(OPCODE_SM_UNK20);
}

/*
0F02 0000 002B3B40                           .....+;@
*/

#endif

