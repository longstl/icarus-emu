////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK40_H_
#define _SM_UNK40_H_

void SM_UNK40(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeA("000004D7D13300000000DF00000000000000DF00000000000000DF00000000000000DF00000000000000DF0000000000000001000000DF00000000000000DF00000000000000DF00000000000000DF00000000000000DF0000000000000002000000DF00000000000000DF00000000000000DF00000000000000DF00000000000000DF0000000000000003000000DF00000000000000DF00000000000000DF00000000000000DF00000000000000DF00000000000000");
	pck->PackSend(OPCODE_SM_UNK40);
}
#endif

