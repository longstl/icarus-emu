////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK36_H_
#define _SM_UNK36_H_

void SM_UNK36(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeD(0);
	pck->writeW(0);
	pck->writeB(0);
	pck->PackSend(OPCODE_SM_UNK36);
}
/*
3D02 0000 06 00000000 0000 00               =...........
*/
#endif

