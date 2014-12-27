////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK30_H_
#define _SM_UNK30_H_

void SM_UNK30(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeD(0);
	pck->PackSend(OPCODE_SM_UNK30);
}

/*
1D2A 0000
00 00 00 00                           .*......
*/

#endif

