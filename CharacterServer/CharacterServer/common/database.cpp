////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////


#include "database.h"

//=================================================================================
// 
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
		log::Error(fg, "CSDatabase: DB connecting failure!\n");
		return;
	}
	mysql_autocommit(db, 1);
}

//=================================================================================
// 
//
DATABASE::~DATABASE()
{
	mysql_close(&mysql);
}

//=================================================================================
// 
//
bool DATABASE::IsError()
{
	return error;
}

//=================================================================================
// ���������, ���� �� �������� � �� � ��������� ������ ��� � charname
//
bool DATABASE::CheckCharname(char* charname)
{
	MYSQL_RES* result;
	char query[256];

	sprintf(query, "SELECT * FROM characters WHERE charname='%s';", charname);

	if (mysql_query(db, query))
	{
		log::Error(fg, "CSDatabase: %s\n", mysql_error(db));
		return false;
	}

	result = mysql_store_result(db);
	if (result == NULL)
	{
		log::Error(fg, "CSDatabase: %s\n", mysql_error(db));
		return false;
	}

	if (mysql_num_rows(result) > 0)
	{
		mysql_free_result(result);
		return false;
	}

	mysql_free_result(result);
	return true;
}

//=================================================================================
// ���������� ���������� ���������� ������������� ���������� ��������
//
int DATABASE::GetNumCharacters(uint16 account_id)
{
	MYSQL_RES* result;
	char query[256];

	sprintf(query, "SELECT * FROM characters WHERE account_id='%d';", account_id);

	if (mysql_query(db, query))
	{
		log::Error(fg, "CSDatabase: %s\n", mysql_error(db));
		return 0;
	}

	result = mysql_store_result(db);
	if (result == NULL)
	{
		log::Error(fg, "CSDatabase: %s\n", mysql_error(db));
		return 0;
	}

	long num = mysql_num_rows(result);
	if (num > 0)
	{
		mysql_free_result(result);
		return num;
	}

	mysql_free_result(result);
	return 0;
}

//=================================================================================
// ���������� ��� ��������� �� ��� ID
//
bool DATABASE::GetCharacterName(int charid, char* out)
{
	MYSQL_RES* result;
	MYSQL_ROW row;
	char query[1024];

	sprintf(query, "SELECT charname FROM characters WHERE id='%d';", charid);
	if (mysql_query(db, query))
	{
		log::Error(fg, "CSDatabase: %s\n", mysql_error(db));
		return false;
	}

	result = mysql_store_result(db);
	if (result == NULL)
	{
		log::Error(fg, "CSDatabase: %s\n", mysql_error(db));
		return 0;
	}

	if ((row = mysql_fetch_row(result)))
	{
		strcpy(out, row[0]);
	}
	else
	{
		mysql_free_result(result);
		log::Error(fg, "CSDatabase: %s\n", mysql_error(db));
		return false;
	}

	mysql_free_result(result);

	return true;
}

//=================================================================================
// ���������� pin ��� �� ���������� ID ��������
//
bool DATABASE::GetPinCode(uint16 account_id, char* out)
{
	MYSQL_RES* result;
	MYSQL_ROW row;
	char query[1024];

	sprintf(query, "SELECT code FROM pin_codes WHERE account_id='%d';", account_id);
	if (mysql_query(db, query))
	{
		log::Error(fg, "CSDatabase: %s\n", mysql_error(db));
		return false;
	}

	result = mysql_store_result(db);
	if (result == NULL)
	{
		log::Error(fg, "CSDatabase: %s\n", mysql_error(db));
		return 0;
	}

	if ((row = mysql_fetch_row(result)))
		strcpy(out, row[0]);
	else
	{
		mysql_free_result(result);
		log::Error(fg, "CSDatabase: %s\n", mysql_error(db));
		return false;
	}

	mysql_free_result(result);
	return true;
}

//=================================================================================
// ���������� ����� PIN ���
//
bool DATABASE::SetPinCode(uint16 account_id, char* pin)
{
	char query[1024];

	sprintf(query, "INSTERT INTO pin_codes VALUES(%d, '%s', 0, 0);", (int)account_id, pin);
//	sprintf(query, "UPDATE pin_codes SET code = '%s' WHERE account_id='%d';", pin, account_id);
	if (mysql_query(db, query))
	{
		log::Error(fg, "CSDatabase: %s\n", mysql_error(db));
		return false;
	}
	return true;
}

//=================================================================================
// ��������� ���������� � PIN ����
//
bool DATABASE::UpdatePinCode(uint16 account_id, int errors)
{
	char query[1024];
	time_t rawTime;
	time(&rawTime);

	sprintf(query, "UPDATE pin_codes SET errors = '%d', date='%d' WHERE account_id='%d';", errors, rawTime, (int)account_id);
	if (mysql_query(db, query))
	{
		log::Error(fg, "CSDatabase: %s\n", mysql_error(db));
		return false;
	}
	return true;
}


//=================================================================================
// �������� ��������� � ��
// ��������� �� �����:
//	charname - ��� ���������
//	st - ��������� �� ��������� CHAR_STYLE ������������ ����� ���������
//	sex - ���
//	cls - �����
//	account_id
//
int DATABASE::CreateCharacter(char* charname, CHAR_STYLE* st, int8 sex, int cls, uint16 account_id)
{
	MYSQL_RES* result;
	MYSQL_ROW row;
	char query[1024];
	int character_id;

	sprintf(query, "REPLACE INTO characters SET charname='%s', class='%d', sex=%d, account_id=%d;", charname, cls, sex, account_id);

	if (mysql_query(db, query))
	{
		log::Error(fg, "CSDatabase: %s\n", mysql_error(db));
		return 0;
	}

	sprintf(query, "SELECT id FROM characters WHERE charname='%s' AND class='%d' AND sex=%d AND account_id=%d;", charname, cls, sex, account_id);
	if (mysql_query(db, query))
	{
		log::Error(fg, "CSDatabase: %s\n", mysql_error(db));
		return 0;
	}

	result = mysql_store_result(db);
	if (result == NULL)
	{
		log::Error(fg, "CSDatabase: %s\n", mysql_error(db));
		return 0;
	}

	if ((row = mysql_fetch_row(result)))
	{
		character_id = atoi(row[0]);
	}
	else
	{
		mysql_free_result(result);
		log::Error(fg, "CSDatabase: %s\n", mysql_error(db));
		return 0;
	}

	mysql_free_result(result);

	sprintf(query, "./data/characters/styles/%d.dat", character_id);
	FILE* ftmp = fopen(query, "wb");
	if (ftmp == NULL)
	{
		log::Error(fg, "CSDatabase: Can't create character style. ID: %d\n", character_id);
		return 0;
	}
	fwrite(st, sizeof(CHAR_STYLE), 1, ftmp);
	fclose(ftmp);



	/*
	sprintf(query, "INSERT INTO character_style VALUES( %d, '%s');", character_id, newbuf);
	delete(newbuf);
	if (mysql_query(db, query))
	{
		log::Error(fg, "MYSQL: %s\n", mysql_error(db));
		return 0;
	}
	*/
	return character_id;
}

//================================================================================
// ASCII to HEX
//
void DATABASE::AtoH(char* in, char* out)
{
	int step = 0;
	char tmp[3];
	memset(tmp, 0, 3);

	for (int i = 0; i < (sizeof(CHAR_STYLE)*2); i += 2)
	{
		strncpy(tmp, in+i, 2);
		out[step] = (uint8)strtol(tmp, NULL, 16);
		++step;
	}
}

//================================================================================
// ��������� ���������� � ���� ���������� ��������
//
int DATABASE::GetCharactersInfo(uint16 account_id, CHARACTER* character_list, int max_characters)
{
	MYSQL_RES* result;
	MYSQL_ROW row;
	char query[256];
	int num_characters = 0;

	sprintf(query, "SELECT id, charname, class, level, sex, access FROM characters WHERE account_id='%d';", account_id);

	if (mysql_query(db, query))
	{
		log::Error(fg, "CSDatabase: %s\n", mysql_error(db));
		return 0;
	}

	result = mysql_store_result(db);
	if (result == NULL)
	{
		log::Error(fg, "CSDatabase: %s\n", mysql_error(db));
		return 0;
	}

	size_t convertedChars;

	while ((row = mysql_fetch_row(result)))
	{
		character_list[num_characters].id = atoi(row[0]);

		convertedChars = 0;
		memset(character_list[num_characters].charname, 0, 20);
		mbstowcs_s(&convertedChars, character_list[num_characters].charname, strlen(row[1])+1, row[1], _TRUNCATE);

		character_list[num_characters].cls = (int8)atoi(row[2]);
		character_list[num_characters].lvl = (int8)atoi(row[3]);
		character_list[num_characters].sex = (int8)atoi(row[4]);

		if (strstr(row[5], "ADMINISTRATOR"))
			character_list[num_characters].access = ACCESS_CHARACTER_ADMINISTRATOR;
		else if (strstr(row[5], "GAMEMASTER"))
			character_list[num_characters].access = ACCESS_CHARACTER_GAMEMASTER;
		else
			character_list[num_characters].access = ACCESS_CHARACTER_PLAYER;


		++num_characters;
		if (num_characters > max_characters)
		{
			--num_characters;
			break;
		}
	}

	mysql_free_result(result);

	for (int i = 0; i < max_characters; i++)
	{
		if (character_list[i].id == 0)
			break;

		sprintf(query, "./data/characters/styles/%d.dat", character_list[i].id);
		FILE* ftmp = fopen(query,"rb");
		if (ftmp == NULL)
		{
			log::Error(fg, "CSDatabase: Can't find character style. ID: %d\n", character_list[i].id);
			return num_characters;
		}
		fread(&character_list[i].style, sizeof(CHAR_STYLE), 1, ftmp);
		fclose(ftmp);
/*
		sprintf(query, "SELECT style FROM character_style WHERE character_id='%d';", character_list[i].id);
		if (mysql_query(db, query))
		{
			log::Error(fg, "MYSQL: %s\n", mysql_error(db));
			return num_characters;
		}

		result = mysql_store_result(db);
		if (result == NULL)
		{
			log::Error(fg, "MYSQL: %s\n", mysql_error(db));
			return num_characters;
		}

		if ((row = mysql_fetch_row(result)))
		{

			AtoH(row[0], (char*)&character_list[i].style);
		}
		mysql_free_result(result);
*/
	}

	return num_characters;
}

//================================================================================
// �������� ��������� �� ��
//
bool DATABASE::DeleteCharacter(uint16 character_id)
{
	char query[256];

	sprintf(query, "DELETE FROM characters WHERE id = %d;", character_id);

	if (mysql_query(db, query))
	{
		log::Error(fg, "CSDatabase: %s\n", mysql_error(db));
		return false;
	}

	sprintf(query, "DELETE FROM character_style WHERE character_id = %d;", character_id);

	if (mysql_query(db, query))
	{
		log::Error(fg, "CSDatabase: %s\n", mysql_error(db));
		return false;
	}

	return true;
}