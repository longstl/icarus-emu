////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK10_H_
#define _SM_UNK10_H_

void SM_UNK10(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeD(0);
	pck->writeUstr(L"35784hj/");
	pck->PackSend(OPCODE_SM_UNK10);
}

/*
..........3.5.7.8.4.h.j./...
0E91
0000
00000000
0800 - num symbols
3300350037013800340068006A002F010000               

*/

#endif

