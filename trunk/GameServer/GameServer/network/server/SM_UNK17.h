////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK17_H_
#define _SM_UNK17_H_

void SM_UNK17(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeD(0);
	pck->writeD(0);
	pck->PackSend(OPCODE_SM_UNK17);
}

/*
0EA1 0000 00000000 00000000               ............
*/

#endif

