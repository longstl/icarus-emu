////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////
#ifndef _SM_PONG_H_
#define _SM_PONG_H_

void SM_PONG(PACKET* pck, bool request = false)
{
	if (request)
	{
		pck->CreateBufForSend();
		pck->writeB(0);
		pck->writeW(0xfe);
		pck->PackSend(OPCODE_SM_PONG);
		SM_UPDATESERVERINFO(pck);
	}
}

#endif