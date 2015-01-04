////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_DELETECHARACTER_H_
#define _SM_DELETECHARACTER_H_

void SM_DELETECHARACTER(PACKET* pck, int character_id)
{
//	if (pck->sql->DeleteCharacter(character_id))
	char charname[32];
	memset(charname, 0, 32);

	pck->sql->DeleteCharacter(character_id);
	pck->sql->GetCharacterName(character_id, charname);
	log::Info(fg, "CSNetwork [%s]: user delete character: %s (account id: %d)\n", inet_ntoa(account->from), charname, account->account_id);

	pck->CreateBufForSend();
	pck->writeD(0);
	pck->writeD(character_id);
	pck->writeD(10);
	pck->writeD(0);
	pck->writeW(0x66);
	pck->writeW(0);
	pck->writeD(0);
	pck->PackSend(OPCODE_SM_DELETECHARACTER);

	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeD(character_id);
	pck->writeD(0x00013601);
	pck->PackSend(0x1705);
}

/*
1e00 0516 
0000 
00000000
7e6f2500 id
0a000000
00000000
0000
64
02
00000000

0e00
0517
0000
7e6f2500
01360100

*/
#endif


