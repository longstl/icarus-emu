////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK11_H_
#define _SM_UNK11_H_

void SM_UNK11(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeD(0);
	pck->PackSend(OPCODE_SM_UNK11);


}

/*
0ED3 0000 00000000                           ........

*/

#endif

