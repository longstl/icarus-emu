////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_CONNECT_H_
#define _SM_CONNECT_H_

void SM_CONNECT(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(0x32);
	pck->writeD(1);
	pck->PackSend(OPCODE_SM_CONNECT);
	
}

/*
0E02
0000
00000000
00000000
32000000
04000000
*/

#endif