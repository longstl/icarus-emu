////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK33_H_
#define _SM_UNK33_H_

void SM_UNK33(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeA("000004CE00000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000200000000000000000000000000000000000000000000000000000000000000000000000000000003000000000000000000000000000000000000000000000000000000000000000000000000000000");
	pck->PackSend(OPCODE_SM_UNK33);
}
#endif

