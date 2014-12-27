////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////
#pragma once
#include "curl\curl.h"

using namespace std;

#define __INFO SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
#define __ERROR SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_RED | FOREGROUND_INTENSITY);
#define __WARNING SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#define __FILE SetConsoleTextAttribute(hConsole, (WORD)FOREGROUND_BLUE | FOREGROUND_INTENSITY);


typedef struct ELEMENT
{
	unsigned __int32	step[10];
} ELEMENT;

struct HEAD_ELEMENTS
{
	unsigned __int8		head_elem_num;
	unsigned __int8		head_elem_size;
	char				head_elem_txt[32];
};

typedef struct ELMDATA
{
	WCHAR				dat[10][1024];
} ELMDATA;

HANDLE					hConsole;
CURL*					curl;
CURLcode				res;
ELEMENT*				elm;
ELMDATA*				elmdata;
unsigned __int16		num_head_elements;
unsigned __int16		num_elements;
HEAD_ELEMENTS			hd_elements[32];
FILE*					hSXB;
FILE*					fr;
unsigned __int32		all_elements_size;
unsigned __int32		data_step;
int						isoldselected;
char					tmp_translate[512];
static string			buffer;