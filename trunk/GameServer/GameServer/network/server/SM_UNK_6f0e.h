////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK_6f0e_H_
#define _SM_UNK_6f0e_H_

void SM_UNK_6f0e(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeD(0);
	pck->PackSend(OPCODE_SM_UNK_6f0e);
}

/*
0E6F 0000 00 00 00 00                           .o......
*/

#endif

