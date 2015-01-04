////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_CHANGE_CHARACTER_H_
#define _SM_CHANGE_CHARACTER_H_

inline void SM_CHANGE_CHARACTER(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeB(1);
	pck->PackSend(OPCODE_SM_CHANGE_CHARACTER);
}

/*
                      ........
*/

#endif

