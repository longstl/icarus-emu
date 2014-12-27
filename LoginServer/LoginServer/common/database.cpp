////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#include "database.h"

//====================================================================
// �����֬լ֬ݬ֬߬ڬ� �ܬݬѬ��� �լݬ� ��ѬҬ��� �� ����
//
DATABASE::DATABASE(FILE* fg, char* db_host, char* db_user, char* db_pass, char* db_name)
{
	error = false;
	this->fg = fg;
	mysql_init(&mysql);
	db = mysql_real_connect(&mysql,
		    db_host,
		    db_user,
		    db_pass,
		    db_name,
		    0, 0, 0);
	if (db == NULL)
	{
		error = true;
		log::Notify(fg, "\n");
		log::Error(fg, "DB connecting failure!\n");
		return;
	}
	mysql_autocommit(db, 1);
}

//====================================================================
// ���Ѭ٬Ҭ�� �ܬݬѬ��� ��ѬҬ��� �� ����
//
DATABASE::~DATABASE()
{
	mysql_close(&mysql);
}

//====================================================================
// ����٬Ӭ�Ѭ�Ѭ֬� true, �֬�ݬ� �Ҭ�ݬ� ���ڬҬܬ� ���� �Ӭ���ݬ߬֬߬ڬ� ���߬ܬ�ڬ� mysql
//
bool DATABASE::IsError()
{
	return error;
}

bool DATABASE::CheckAccountName(char* password, char* hash)
{
	MYSQL_RES* result;
	MYSQL_ROW row;
	char query[256];

	sprintf(query, "SELECT login FROM accounts WHERE password='%s';", password);

	if (mysql_query(db, query))
	{
		log::Error(fg, "MYSQL: %s\n", mysql_error(db));
		return false;
	}

	result = mysql_store_result(db);
	if (result == NULL)
	{
		log::Error(fg, "MYSQL: %s\n", mysql_error(db));
		return false;
	}

	if ((row = mysql_fetch_row(result)))
	{
		sprintf(query, "UPDATE accounts SET hash='%s' WHERE login='%s';", hash, row[0]);
		mysql_free_result(result);

		if (mysql_query(db, query))
		{
			log::Error(fg, "MYSQL: %s\n", mysql_error(db));
			return false;
		}
		return true;
	}
	mysql_free_result(result);
	return false;
}

bool DATABASE::GetAccountName(char* hash, char* out, int* id_account)
{
	MYSQL_RES* result;
	MYSQL_ROW row;
	char query[256];

	sprintf(query, "SELECT login,id FROM accounts WHERE hash='%s';", hash);
	if (mysql_query(db, query))
	{
		log::Error(fg, "MYSQL: %s\n", mysql_error(db));
		return false;
	}

	result = mysql_store_result(db);
	if (result == NULL)
	{
		log::Error(fg, "MYSQL: %s\n", mysql_error(db));
		return false;
	}

	if ((row = mysql_fetch_row(result)))
	{
		strcpy(out, row[0]);
		id_account[0] = atoi(row[1]);
		mysql_free_result(result);
		return true;
	}
	mysql_free_result(result);
	return false;
}

int DATABASE::GetServerList(char* buf)
{
/*	MYSQL_RES* result;
	MYSQL_ROW row;
	char query[256];

	sprintf(query, "SELECT * FROM servers;", hash);
	if (mysql_query(db, query))
	{
		log::Error(fg, "MYSQL: %s\n", mysql_error(db));
		return 0;
	}

	result = mysql_store_result(db);
	if (result == NULL)
	{
		log::Error(fg, "MYSQL: %s\n", mysql_error(db));
		return 0;
	}

	int numservers = 0;
	while ((row = mysql_fetch_row(result)))
	{
		strcpy(out, row[0]);
		id_account[0] = atoi(row[1]);
		mysql_free_result(result);
		++numservers;
	}
	mysql_free_result(result);
	return numservers;*/
	return 0;
}