////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK21_H_
#define _SM_UNK21_H_

void SM_UNK21(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeB(5);
	pck->writeW(0x0100);
	pck->writeW(0x010b);
	pck->writeW(0x010c);
	pck->writeW(0x010f);
	pck->writeW(0x0113);
	pck->PackSend(OPCODE_SM_UNK21);
}

/*
0F03 0000 05 0001 0B01 0C01 0F01 1301      ...............
*/

#endif

