////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////
#ifndef _CM_AUTH_H_
#define _CM_AUTH_H_

void CM_AUTH(PACKET* pck)
{
	char hash[64];
	char login[32];
	uint16 unk1 = pck->readW();
	uint8 unk2 = pck->readB();
	int len_hash = pck->readTstr(hash);

	if ((pck->sockstruct->mysql->GetAccountName(hash, login, &pck->sockstruct->account_id)))
	{
		strcpy(pck->sockstruct->account_name, login);
		SM_AUTH(pck, login, true);
	}
	else
	{
		SM_AUTH(pck, hash, false);
	}
}

/*
// 1.5.48
21:54:44 [DEBUG] ...76000b0302ffffff900232303134313231333231353330375153454f716f6b49714d734b4f4f7167634b0017001cffffffcc160300ffffffcc160310000000ffffffe84affffff8a57ffffffc048ffffff8a57ffffffb0ffffffc22dffffffba003370ffffffbbffffff8bffffffff7f3f05000000ffffffb7ffffffc4100068ffffffb117004b0cffffff81576063ffffff8a5700ffffffcc1603000000000a00000008000000ffffffb7ffffffc410005000ffffff8157


*/

#endif _CM_AUTH_H_



