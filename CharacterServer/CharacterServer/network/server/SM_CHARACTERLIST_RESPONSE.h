////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_CHARACTERLIST_RESPONSE_H_
#define _SM_CHARACTERLIST_RESPONSE_H_

void SM_CHARACTERLIST_RESPONSE(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeD(0); // unk
	pck->writeB(1); // unk

	int num_characters = pck->sql->GetCharactersInfo(pck->sockstruct->account_id, pck->sockstruct->character, max_characters);
	if (num_characters == 20)
	{
		pck->writeB(1);
		pck->writeW(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->PackSend(OPCODE_SM_CHARACTERLIST_RESPONSE);
		return;
	}

	if (num_characters >= max_characters)
		pck->writeB(DENY_CREATE_CHARACTER);						// deny create character
	else
		pck->writeB(ALLOW_CREATE_CHARACTER);					// access create character

	pck->writeW(num_characters);								// max characters in server
	pck->writeD(pck->sockstruct->character[0].id);
	pck->writeD(0);
	for (int i = 0; i < num_characters; i++)
	{
		pck->writeD(pck->sockstruct->character[i].id);
		pck->writeBuf((void*)&pck->sockstruct->character[i].charname, 20);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeW(0);
		pck->writeW(0);
		pck->writeW(1);
		pck->writeW(1);
		pck->writeW(pck->sockstruct->character[i].cls);
		pck->writeW(1);
		pck->writeD(1);
		pck->writeW(pck->sockstruct->character[i].lvl);		// level
		pck->writeB(pck->sockstruct->character[i].sex);		// sex
		pck->writeB(0);
		pck->writeB(12);
		pck->writeB(0);
		pck->writeB(0);
		pck->writeB(0);
		pck->writeD(0x433f0000);
		pck->writeD(0x44580800);
		pck->writeD(0x42c40000);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0xb1000000);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0xffffffff);
		pck->writeD(0);
		pck->writeD(0xffffffff);
		pck->writeD(0xffffffff);
		pck->writeD(0xffffffff);
		pck->writeD(0);
		pck->writeD(0xd9efa578);
		pck->writeD(2);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0x02800000);
		pck->writeB(0x32);
		pck->writeB(23);			// minuta sozdaniya persa
		pck->writeB(0x2);			// chas sozdaniya persa
		pck->writeB(0x3);			// den sozdaniya persa

		pck->writeB(0x0e);			// mesac sozdaniya persa
		pck->writeB(0x0b);			// god sozdaniya persa
		pck->writeW(0x0000);
		pck->writeD(0x0145);
		pck->writeD(0);
		pck->writeD(0x0001006c);
		pck->writeD(0xffff0000);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0xffffffff);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0xffffffff);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0x0001006d);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0xffffffff);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0xffffffff);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0xffffffff);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0xffffffff);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0xffffffff);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0xffffffff);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0xffffffff);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeBuf((void*)&pck->sockstruct->character[i].style, sizeof(CHAR_STYLE));
		pck->writeW(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
		pck->writeD(0);
	}
	pck->PackSend(OPCODE_SM_CHARACTERLIST_RESPONSE);
}

#endif


/*
5602
0511
0000
00000000
0100
0100
7e6f2500
00000000
7e6f2500
46006c0061007900730000000000000000000000
00000000
00000000
00000000
00000000
00000000
01000000
01000000
0c000000
0000
3f43
0080
58440000
c4420000
00000000
00000000
0000b100
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
0000
ffffffff
00000000
ffffffff
ffffffff
ffffffff
00000000
78a5efd9
02000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00008002
321d011b
0b0e0000
45010000
00000000
6c000100
0000ffff
00000000
00000000
ffffffff
00000000
00000000
00000000
ffffffff
00000000
00000000
00000000
6d000100
00000000
00000000
00000000
ffffffff
00000000
00000000
00000000
ffffffff
00000000
00000000
00000000
ffffffff
00000000
00000000
00000000
ffffffff
00000000
00000000
00000000
ffffffff
00000000
00000000
00000000
ffffffff
00000000
00000000
00000000
ffffffff
00000000
00000000
00000000
813ecb32062b1427b336993ae12e6a4200008504ffffffffecff1300ffffffff111d2bffc1c1c1ff565656ffb8daa7ff707070ff000000ff000000ff000000ffffffffffffffffff3f33c105b3caf2f0da03100dc7fd1ed4b3e5ca0000000000000000000000003800452f64fc07000000000000e3fcdfc6ec00004700000000000000640000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

¬Ö¬ã¬Ý¬Ú ¬ß¬Ö¬ä ¬é¬Ñ¬â¬à¬Ó
[1600][0511]
0000
00000000
01000000
00000000
00000000
*/