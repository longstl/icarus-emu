////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////
#ifndef _SM_AUTH_H_
#define _SM_AUTH_H_

void SM_AUTH(PACKET* pck, char* login, bool succesful)
{
	if (!succesful)
		closesocket(pck->sockstruct->socket);

	struct sockaddr_in from;
	int len = sizeof(from);
	getpeername(pck->sockstruct->socket, (struct sockaddr *)&from, &len);
	log::Info(fg, "Connected account: [%s] %s\n", inet_ntoa(from.sin_addr), pck->sockstruct->account_name);

	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeW(0);
	pck->writeW(0);
	pck->writeBuf(pck->sockstruct->account_name, 124);
	pck->writeD(0x00010100);
	pck->PackSend(OPCODE_SM_AUTH);
}

#endif