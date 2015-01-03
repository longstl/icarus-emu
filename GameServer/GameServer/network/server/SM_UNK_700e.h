////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_UNK_700e_H_
#define _SM_UNK_700e_H_

inline void SM_UNK_700e(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeB(1);
	pck->PackSend(OPCODE_SM_UNK_700e);
}

/*
                      ........
*/

#endif

