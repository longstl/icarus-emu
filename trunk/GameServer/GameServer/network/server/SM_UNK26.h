////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK26_H_
#define _SM_UNK26_H_

void SM_UNK26(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeD(0x8004be84);
	pck->writeD(0x9e73);
	pck->writeD(1);
	pck->writeD(1);
	pck->writeD(0x8004be84);
	pck->writeD(0x000701ff);
	pck->writeD(0);
	pck->PackSend(OPCODE_SM_UNK26);
}

/*
1823 0000
84BE0480
739E0000
01000000
01000000
84BE0480
FF010700
00000000
*/

#endif

