////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////
#ifndef _SM_SERVER_LIST_H_
#define _SM_SERVER_LIST_H_

void SM_SERVER_LIST(PACKET* pck)
{
	char srv[42];
	WCHAR	wcstring[42];
	size_t convertedChars = 0;

	time_t rawTime;
	time(&rawTime);

	int num_servers = 0;
	for (int i = 0; i < 12; i++)
	{
		if (pck->sockstruct->gameservers_info[i].id != -1)
			++num_servers;
	}

	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeD(0);
	pck->writeD(5);
	pck->writeD(num_servers); // for

	for (int i = 0; i < 12; i++)
	{
		if (pck->sockstruct->gameservers_info[i].id != -1)
		{
			if ((pck->sockstruct->gameservers_info[i].timeupdate + 10 * 60 * 1000) < rawTime)
				continue;

			int max_players = pck->sockstruct->gameservers_info[i].players_max;
			int players = pck->sockstruct->gameservers_info[i].players_connected;

			pck->writeD(pck->sockstruct->gameservers_info[i].id);
			memset(wcstring, 0, sizeof(wcstring)-1);
			mbstowcs_s(&convertedChars, wcstring, strlen(pck->sockstruct->gameservers_info[i].name) + 1, pck->sockstruct->gameservers_info[i].name, _TRUNCATE);
			memcpy(srv, wcstring, convertedChars * 2);
			pck->writeBuf(srv, 42);
			pck->writeW(1); // unk
			pck->writeD(0); // unk

			if ((max_players / 4 * 1) > players) {
				pck->writeD(0);
			}
			else if ((max_players / 4 * 2) < players) {
				pck->writeD(1);
			}
			else if ((max_players / 4 * 3) < players) {
				pck->writeD(2);
			}
			else {
				pck->writeD(3);
			}

			pck->writeB(0);
			pck->writeB(2);
			pck->writeW(1);
		}
	}


/*	pck->writeD(1); // poradkoviy nomer servera
	pck->writeBuf(srv, 42); // imya servera (max 42 sym)
	pck->writeW(1);
	pck->writeD(0);
	pck->writeD(0); // zagrujennost servera: 0-comfort, 1-general, 2 - confusion, 3 - saturation, 4 - check in, 5 - unknown
	pck->writeB(0); // kolichestvo persov
	pck->writeB(2); // Послед?я колонк?
	pck->writeW(1); 
*/
	pck->PackSend(OPCODE_SM_SERVER_LIST);
	pck->sockstruct->send_serverlist = true;
}

#endif



