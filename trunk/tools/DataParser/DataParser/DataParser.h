#pragma once

#include "curl\curl.h"

struct KEYS
{
	__int8		unk;
	__int8		size;
	char		name[256];
};

HANDLE					hConsole;
FILE*					fLog;
FILE*					fResult;
FILE*					freal;
char					filename[MAX_PATH];
char					short_filename[MAX_PATH];
KEYS					keys[256];
CURL*					curl;
CURLcode				res;
char					tmp_translate[512];
char*					offsets;
bool					translate;

char					xml00[] = "<blocks>\n";
char					xml01[] = "</blocks>\n";
char					xml1[] = "\t<block id=\"%s\" ";
char					xml2[] = "use=\"%d\" ";
char					xml3[] = "type=\"%d\" ";
char					xml4[] = "target_id=\"%d\" ";
char					xml5[] = "conditions=\"%d\" ";
char					xml6[] = "name=\"%s\" />\n";

char					xml_s[] = "\t <block ";
char					xml_e[] = "/>\n";
char					xml_t1[] = "=\"";
char					xml_t2[] = "\" ";



void wstring_to_utf8_hex(char* output, WCHAR* input);
void Translat(WCHAR* txt);
typedef void(*LPSEARCHFUNC)(LPCTSTR lpszFileName);