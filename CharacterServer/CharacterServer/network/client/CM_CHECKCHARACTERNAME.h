////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_CHECKCHARACTERNAME_H_
#define _CM_CHECKCHARACTERNAME_H_

void CM_CHECKCHARACTERNAME(PACKET* pck)
{
	char charname[18];
	WCHAR w_charname[18];
	int len_w_charname = pck->readWstr(w_charname);
	int len_charname = wcstombs(charname, w_charname, 18);

	if (len_charname < 4 || len_charname > 16)
	{
		SM_LOBBYUSERMSG(pck, 14);					// �ܬ�ݬڬ�֬��Ӭ� ��ڬެӬ�ݬ�� �� charname �߬֬լ�����ڬެ�
		return;
	}

	if (!(pck->sql->CheckCharname(charname)))
	{
		SM_LOBBYUSERMSG(pck, 14);
		return;
	}

	SM_LOBBYUSERMSG(pck, 0);
	
}

#endif