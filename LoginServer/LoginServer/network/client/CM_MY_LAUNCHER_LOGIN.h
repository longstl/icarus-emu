////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////
#ifndef _CM_MY_LAUNCHER_LOGIN_H_
#define _CM_MY_LAUNCHER_LOGIN_H_

#include <time.h>

void CM_MY_LAUNCHER_LOGIN(PACKET* pck)
{
	int rnd;
	char recv[256];
	char hash[256];

	memset(hash, 0, sizeof(recv));
	pck->readTstr(recv);

	// ¬æ¬à¬â¬Þ¬Ú¬â¬à¬Ó¬Ñ¬ß¬Ú¬Ö ¬ç¬ï¬ê¬Ñ (32 ¬Ò¬Ñ¬Û¬ä¬Ñ)
	memset(hash, 0, sizeof(hash));
	srand(GetTickCount());

	uint8 oric;
	int n = 0;
	for (int i = 0; i < 32; i++)
	{
		oric = 0x41;
		rnd = rand();
		if (rnd % 2)
			oric += 0x20;

		rnd = (rand() % 24) | oric;
		rnd = rnd & 0xff;
		memset(hash + n, rnd, 1);
		++n;
	}

	char times[16];
	time_t tms;
	time(&tms);
	tm* timeinfo = localtime(&tms);
	sprintf(times, "%d%02i%02i%02i%02i%02i", timeinfo->tm_year + 1900,
											 timeinfo->tm_mon + 1,
											 timeinfo->tm_mday,
											 timeinfo->tm_hour,
											 timeinfo->tm_min,
											 timeinfo->tm_sec);
	memcpy(hash, times, strlen(times));


	if (!(pck->sockstruct->mysql->CheckAccountName(recv, hash)))
	{
		memset(hash, 0, sizeof(hash));
	}

	SM_MY_LAUNCHER_LOGIN(pck, hash);
}

#endif _CM_MY_LAUNCHER_LOGIN_H_



