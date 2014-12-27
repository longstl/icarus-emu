////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <winsock.h>
#include "mysql\mysql.h"
#include "../defines.h"
#include "logger.h"

class DATABASE
{

public:
	DATABASE(FILE* fg, char* db_host, char* db_user, char* db_pass, char* db_name);
	~DATABASE();
	bool IsError();

	bool CheckAccountName(char* password, char* hash);					/* ����٬Ӭ�Ѭ�Ѭ֬� true, �֬�ݬ� �� ���� �߬Ѭ۬լ֬� ��֬�֬լѬӬѬ֬ެ�� ��Ѭ��ݬ� �� �٬Ѭ�ڬ��ӬѬ֬� ���� */
	bool GetAccountName(char* hash, char* out, int* id_account);		/* ����٬Ӭ�Ѭ�Ѭ֬� �ݬ�Ԭڬ�, �֬�ݬ� �� ���� �߬Ѭ۬լ֬� ��֬�֬լѬӬѬ֬ެ�� ���� */
	int GetServerList(char* buf);										/* ����٬Ӭ�Ѭ�Ѭ֬� ��֬ݬ�߬�� �Ҭ��֬� �լݬ� �����ܬ��� SERVER_INFO */


private:
	MYSQL			mysql;
	MYSQL*			db;
	FILE*			fg;				// ���߬լ� �լݬ� �ݬ�Ԭ֬��
	bool			error;
};


#endif



