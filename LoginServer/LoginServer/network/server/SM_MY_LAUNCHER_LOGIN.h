////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////
#ifndef _SM_MY_LAUNCHER_LOGIN_H_
#define _SM_MY_LAUNCHER_LOGIN_H_

void SM_MY_LAUNCHER_LOGIN(PACKET* pck, char* hash)
{
	pck->CreateBufForSend();
//	pck->writeW(0);
	pck->writeTstr(hash);
	pck->PackSend(OPCODE_SM_MY_LAUNCHER_LOGIN);
}

#endif SM_MY_LAUNCHER_LOGIN