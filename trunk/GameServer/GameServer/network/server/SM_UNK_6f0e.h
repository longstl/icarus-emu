////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK_6f0e_H_
#define _SM_UNK_6f0e_H_

inline void SM_UNK_6f0e(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeD(0);
	pck->PackSend(OPCODE_SM_UNK_6f0e);
	SM_CHANGE_CHARACTER(pck);
}

/*
0E6F 0000 00 00 00 00                           .o......
*/

#endif

