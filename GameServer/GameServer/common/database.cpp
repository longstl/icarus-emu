////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////
#include "database.h"

//=================================================================================
// Create DATABASE class
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

//=================================================================================
// delete DATABASE class
//
DATABASE::~DATABASE()
{
	mysql_close(&mysql);
}

//=================================================================================
// error in MySQL
//
bool DATABASE::IsError()
{
	return error;
}

//================================================================================
// convert ascii string to hex data
//
void DATABASE::AtoH(char* in, char* out)
{
	int step = 0;
	char tmp[3];
	memset(tmp, 0, 3);

	for (int i = 0; i < (int)strlen(in); i+=2)
	{
		strncpy(tmp, in+i, 2);
		out[step] = (int)strtol(tmp, NULL, 16);
		++step;
	}
}

//================================================================================
// Get character info
//
bool DATABASE::GetCharacterInfo(uint32 character_id, CHARACTER* character)
{
	MYSQL_RES* result;
	MYSQL_ROW row;
	char query[256];

	sprintf(query, "SELECT charname, class, level, sex, pos_x, pos_y, pos_z, rotate, access FROM characters WHERE id='%d';", character_id);

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

	size_t convertedChars;

	if ((row = mysql_fetch_row(result)))
	{
		character->id = character_id;

		convertedChars = 0;
		memset(character->charname, 0, 20);
		mbstowcs_s(&convertedChars, character->charname, strlen(row[0])+1, row[0], _TRUNCATE);

		character->cls = atoi(row[1]);
		character->lvl = atoi(row[2]);
		character->sex = atoi(row[3]);
		if (row[4] != NULL)
			character->pos_x = atof(row[4]);
		if (row[5] != NULL)
			character->pos_y = atof(row[5]);
		if (row[6] != NULL)
			character->pos_z = atof(row[6]);
		if (row[7] != NULL)
			character->rotate = atof(row[7]);

		if (strstr(row[8], "ADMINISTRATOR"))
			character->access = ACCESS_CHARACTER_ADMINISTRATOR;
		else if (strstr(row[8], "GAMEMASTER"))
			character->access = ACCESS_CHARACTER_GAMEMASTER;
		else
			character->access = ACCESS_CHARACTER_PLAYER;
	}
	else
	{
		log::Error(fg, "MYSQL: %s\n", mysql_error(db));
		mysql_free_result(result);
		return false;
	}

	mysql_free_result(result);

	sprintf(query, "./data/characters/styles/%d.dat", character_id);
	FILE* ftmp = fopen(query, "rb");
	if (ftmp == NULL)
	{
		log::Error(fg, "MYSQL: Can't find character style. ID: %d\n", character_id);
		return false;
	}
	fread(&character->style, sizeof(CHAR_STYLE), 1, ftmp);
	fclose(ftmp);

	return true;
}