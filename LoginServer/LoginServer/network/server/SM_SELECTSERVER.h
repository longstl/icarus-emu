////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////
#ifndef _SM_SELECTSERVER_H_
#define _SM_SELECTSERVER_H_

void SM_SELECTSERVER(PACKET* pck, int numserver)
{
	if (pck->sockstruct->gameservers_info[numserver].id == -1)
	{
		return;
	}
	pck->CreateBufForSend();
	pck->writeW(0);	// unk
	pck->writeW(0); // unk
	pck->writeW(0); // unk
	pck->writeD(pck->sockstruct->gameservers_info[numserver].cs_ip); // ip
	pck->writeD(pck->sockstruct->gameservers_info[numserver].cs_port); // port
	pck->writeD(0x001356e2); // unk
//	pck->writeW(0xa462); // unk
	pck->writeD(pck->sockstruct->account_id); // id
	pck->PackSend(OPCODE_SM_SELECTSERVER);
};

#endif 