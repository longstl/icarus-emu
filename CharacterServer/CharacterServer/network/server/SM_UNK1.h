////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK1_H_
#define _SM_UNK1_H_

void SM_UNK1(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0x0301);
	pck->writeD(0x02040101);
	pck->PackSend(OPCODE_SM_UNK1);
}

#endif