////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_USE_SKILL_H_
#define _SM_USE_SKILL_H_

inline void SM_USE_SKILL(PACKET* pck, int unk)
{
	pck->CreateBufForSend();
	pck->writeUD(0);
	pck->writeUD(unk);
	pck->writeUD(0x00000c01);
	pck->writeUD(0xffffffff);
	pck->writeUD(0x40500000);
	pck->PackSend(OPCODE_SM_USE_SKILL);
}
/*
180C 0000
00000000
3C000A00
010C0000   ........<.......
FFFFFFFF
00005040                           ......P@
*/
#endif

