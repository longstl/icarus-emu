// DataParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DataParser.h"

void Parser()
{
	__int16 num_keys;
	__int16 num_offsets;
	int data_step;
	size_t convertedChars = 0;
	wchar_t wcstring[2048];
	char buf[2048];
	int contentLength;

	char commxml_start[] = "<!-- ";
	char commxml_end[] = " -->\n";

	// ðàçáîð çàãîëîâêà

	fread(&num_keys, 2, 1, freal);
	fprintf(fLog, "num_keys: %d\n", num_keys);
	if (num_keys == 0)
		return;

	for (int i = 0; i < num_keys; i++)
	{
		memset(&keys[i].name, 0, 256);
		fread(&keys[i].unk, 1, 1, freal);
		fread(&keys[i].size, 1, 1, freal);
		fread(&keys[i].name, keys[i].size, 1, freal);
		fwrite(commxml_start, strlen(commxml_start), 1, fResult);
		fwrite(&keys[i].name, strlen(keys[i].name), 1, fResult);		

		memset(wcstring, 0, sizeof(wcstring));
		contentLength = MultiByteToWideChar(949, 0, (char*)&keys[i].name, -1, wcstring, convertedChars);
		MultiByteToWideChar(949, 0, (char*)&keys[i].name, -1, wcstring, contentLength);
		Translat(wcstring);

		for (int n = 0; n < strlen(tmp_translate); n++)
		{
			if (tmp_translate[n] == ' ')
				tmp_translate[n] = '_';
			else
			{
				tmp_translate[n] = tolower(tmp_translate[n]);
			}
		}

		strcpy((char*)&keys[i].name, tmp_translate);
		sprintf(buf, " = %s", tmp_translate);
		fwrite(buf, strlen(buf), 1, fResult);			
		fwrite(commxml_end, strlen(commxml_end), 1, fResult);

		printf(commxml_start);
		printf(buf);
		printf(commxml_end);
	}

	// çàãðóçêà îôôñåòîâ
	fread(&num_offsets, 2, 1, freal);
	int offset_buffer_size = num_offsets * num_keys * 4;
	data_step = offset_buffer_size + 4;

	offsets = (char*)malloc(offset_buffer_size + 4);
	memset(offsets, -1, offset_buffer_size + 4);
	fread(offsets, data_step , 1, freal);

	int ss = ftell(freal);
	unsigned __int32 size_keydata = 0;
	void* data;

	int step_xml = 0;

	unsigned __int8 param8;
	unsigned __int16 param16;
	unsigned __int32 param32;
	

	fwrite(xml00, strlen(xml00), 1, fResult);
	printf(xml00);
	
	for (int i = 0; i < num_offsets * num_keys; i++)
	{
		size_keydata = *(reinterpret_cast<unsigned __int32*>(&offsets[(i + 1) * 4])) - *(reinterpret_cast<unsigned __int32*>(&offsets[i * 4]));
		data = malloc(size_keydata + 1);
		memset(data, 0, size_keydata);
		fread(data, size_keydata, 1, freal);

		if (step_xml == 0)
		{
			fwrite(xml_s, strlen(xml_s), 1, fResult);
			printf(xml_s);
		}

		fwrite(&keys[step_xml].name, strlen((const char*)&keys[step_xml].name), 1, fResult);
		fwrite(xml_t1, strlen(xml_t1), 1, fResult);
		printf((const char*)&keys[step_xml].name);
		printf(xml_t1);

		memset(buf, 0, 511);
		int st;
		float ft;
		switch (size_keydata)
		{
		case 0:
			break;
		case 1:
			sprintf(buf, "%d", (unsigned __int8)*(reinterpret_cast<unsigned __int8*>(data)));
			break;
		case 2:
			sprintf(buf, "%d", (unsigned __int16)*(reinterpret_cast<unsigned __int16*>(data)));
			break;
		case 3:
			sprintf(buf, "%d", (unsigned __int16)*(reinterpret_cast<unsigned __int16*>(data)));
			break;
		case 4:
			st = *(reinterpret_cast<unsigned __int32*>(data));
			if (st >= 0x30000000)
			{
				ft = *(float*)&st;
				sprintf(buf, "%f", ft);
			}
			else
			{
				sprintf(buf, "%d", st);
			}
			break;
		default:
			if (translate)
			{
				contentLength = MultiByteToWideChar(949, 0, (char*)data, -1, wcstring, convertedChars);
				MultiByteToWideChar(949, 0, (char*)data, -1, wcstring, contentLength);
				Translat((WCHAR*)wcstring);
				sprintf(buf, "%s", tmp_translate);
			}
			else
			{
				sprintf(buf, "%s", data);
			}
		}

		fwrite(buf, strlen(buf), 1, fResult);
		fwrite(xml_t2, strlen(xml_t2), 1, fResult);
		printf(buf);
		printf(xml_t2);

		free(data);

		++step_xml;
		if (step_xml == num_keys)
		{
			step_xml = 0;
			fwrite(xml_e, strlen(xml_e), 1, fResult);
			printf(xml_e);
		}
			
	}

	fwrite(xml01, strlen(xml01), 1, fResult);
	printf(xml01);
	free(offsets);
	fclose(freal);
	fclose(fResult);
}

//=================================================================================
// Êîíâåðòàöèÿ þíèêîäà â HEX ñòðîêó
//
void wstring_to_utf8_hex(char* output, WCHAR* input)
{
	output[0] = 0;
	int step = 0;
	int cbNeeded = WideCharToMultiByte(CP_UTF8, 0, input, -1, NULL, 0, NULL, NULL);
	if (cbNeeded > 0) {
		char *utf8 = new char[cbNeeded];
		if (WideCharToMultiByte(CP_UTF8, 0, input, -1, utf8, cbNeeded, NULL, NULL) != 0) {
			for (char *p = utf8; *p; *p++) {
				char onehex[5];
				_snprintf(onehex, sizeof(onehex), "%%%02.2X", (unsigned char)*p);
				sprintf(output, "%s%s", output, onehex);
			}
		}
		delete[] utf8;
	}
}

size_t cb(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	char check[] = "\"trans\":\"";
	int step_chk = 0;

	char* settranschar;
	if ((settranschar = strstr(ptr, check)) != NULL)
	{
		settranschar += strlen(check);
		step_chk = 0;
		for (int i = 0; i < size - (settranschar - ptr); i++)
			if (settranschar[i] == 0x22)
			{
				memset(tmp_translate, 0, 512);
				memcpy(tmp_translate, settranschar, i);
				break;
			}
	}
	return size*nmemb;
}

//=================================================================================
// Ïåðåâîäèò óêàçàííóþ ñòðîêó â HEX âèä
// îòïðàâëÿåò ãóãëó äëÿ ïåðåâîäà
//
void Translat(WCHAR* txt)
{
	char aaa[2048];
	char stp[2048];
	memset(aaa, 0, 2048);
	memset(stp, 0, 2048);
	wstring_to_utf8_hex(aaa, txt);

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if (curl)
	{
		sprintf(stp, "http://translate.google.ru/translate_a/t?client=x&text=%s&hl=kr&sl=kr&tl=en", aaa);
		struct curl_slist *chunk = NULL;
		chunk = curl_slist_append(chunk, "Accept: text/html, application/xhtml+xml, */*");
		chunk = curl_slist_append(chunk, "Accept-Language: ru,en-US;q=0.8,en;q=0.5,ko;q=0.3");
		chunk = curl_slist_append(chunk, "User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64; Trident/7.0; rv:11.0) like Gecko");
		chunk = curl_slist_append(chunk, "Connection: Keep-Alive");
		res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

		res = curl_easy_setopt(curl, CURLOPT_URL, stp);
		res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
			MessageBox(NULL, "curl_easy_perform() failed: \n", curl_easy_strerror(res), NULL);
		}
		curl_easy_cleanup(curl);
	}
}

//=================================================================================
// Ñîçäàåì ôàéë äëÿ ðåçóëüòàòà çàìåíÿ ðàñøèðåíèå íà XML
//
bool CreateResultFile(char* fname)
{
	char newfilename[MAX_PATH];
	char drive[12];
	char dir[MAX_PATH];
	char name[MAX_PATH];
	char ext[12];
	_splitpath(fname, drive, dir, name, ext);
	sprintf(short_filename, "%s%s%s%s", drive, dir, name, ext);
	sprintf(newfilename, "%s%s%s.xml", drive, dir, name);

	fResult = fopen(newfilename, "wb");
	if (!fResult)
		return false;

	char xml[] = "<?xml version = \"1.0\"?>\n";
	fwrite(xml, strlen(xml), 1, fResult);

	return true;
}

void DoSomething(LPCTSTR lpszFileName)
{
	strcpy(filename, lpszFileName);
	if (!CreateResultFile((char*)lpszFileName))
	{
		fprintf(fLog, "Can't create result file.\n");
		return;
	}
	freal = fopen(lpszFileName, "rb");
	if (!lpszFileName)
	{
		printf("Can't open file %s\n\n", lpszFileName);
		fprintf(fLog, "Can't open file %s\n\n", lpszFileName);
		return;
	}

	printf("File: %s:\n", short_filename);
	fprintf(fLog, "File: %s:\n", short_filename);
	Parser();
}

BOOL SearchFiles(LPCTSTR lpszFileName, LPSEARCHFUNC lpSearchFunc, BOOL bInnerFolders = TRUE)
{
	LPTSTR part;
	char tmp[MAX_PATH]; // ¬Ó¬â¬Ö¬Þ¬Ö¬ß¬ß¬í¬Û ¬Þ¬Ñ¬ã¬ã¬Ú¬Ó
	char name[MAX_PATH];

	HANDLE hSearch = NULL;
	WIN32_FIND_DATA wfd;
	memset(&wfd, 0, sizeof(WIN32_FIND_DATA));

	// ¬ã¬ß¬Ñ¬é¬Ñ¬Ý¬à ¬á¬à¬Ú¬ã¬Ü ¬Ó¬ß¬å¬ä¬â¬Ú ¬Ó¬Ý¬à¬Ø¬Ö¬ß¬ß¬í¬ç ¬á¬Ñ¬á¬Ü¬Ñ¬ç ...
	if (bInnerFolders)
	{
		if (GetFullPathName(lpszFileName, MAX_PATH, tmp, &part) == 0) return FALSE;
		strcpy(name, part);
		strcpy(part, "*.*");

		// ¬Ö¬ã¬Ý¬Ú ¬á¬Ñ¬á¬Ü¬Ú ¬ã¬å¬ë¬Ö¬ã¬ä¬Ó¬å¬ð¬ä, ¬ä¬à ¬Õ¬Ö¬Ý¬Ñ¬Ö¬Þ ¬á¬à¬Ú¬ã¬Ü
		wfd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
		if (!((hSearch = FindFirstFile(tmp, &wfd)) == INVALID_HANDLE_VALUE))
			do
			{
				// ¬Ó ¬Ü¬Ñ¬Ø¬Õ¬à¬Û ¬á¬Ñ¬á¬Ü¬Ö ¬Ö¬ã¬ä¬î ¬Õ¬Ó¬Ö ¬á¬Ñ¬á¬Ü¬Ú ¬ã ¬Ú¬Þ¬Ö¬ß¬Ñ¬Þ¬Ú "." ¬Ú ".."
				// ¬Ú ¬ï¬ä¬Ú ¬á¬Ñ¬á¬Ü¬Ú ¬Þ¬í ¬ß¬Ö ¬ä¬â¬à¬Ô¬Ñ¬Ö¬Þ

				// ¬á¬â¬à¬á¬å¬ã¬Ü¬Ñ¬Ö¬Þ ¬á¬Ñ¬á¬Ü¬Ú "." ¬Ú ".."
				if (!strncmp(wfd.cFileName, ".", 1) || !strncmp(wfd.cFileName, "..", 2))
					continue;

				if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // ¬Ö¬ã¬Ý¬Ú ¬Þ¬í ¬ß¬Ñ¬ê¬Ý¬Ú ¬á¬Ñ¬á¬Ü¬å
				{
					char next[MAX_PATH];
					if (GetFullPathName(lpszFileName, MAX_PATH, next, &part) == 0) return FALSE;
					strcpy(part, wfd.cFileName);
					strcat(next, "\\");
					strcat(next, name);

					SearchFiles(next, lpSearchFunc, TRUE);
				}
			} while (FindNextFile(hSearch, &wfd)); // ¬Ú¬ë¬Ö¬Þ ¬ã¬Ý¬Ö¬Õ¬å¬ð¬ë¬Ú¬Û ¬æ¬Ñ¬Û¬Ý

			FindClose(hSearch); // ¬Ù¬Ñ¬Ü¬Ñ¬ß¬é¬Ú¬Ó¬Ñ¬Ö¬Þ ¬á¬à¬Ú¬ã¬Ü
	}

	if ((hSearch = FindFirstFile(lpszFileName, &wfd)) == INVALID_HANDLE_VALUE)
		return TRUE; // ¬Ó ¬á¬â¬à¬ä¬Ú¬Ó¬ß¬à¬Þ ¬ã¬Ý¬å¬é¬Ñ¬Ö ¬Ó¬í¬ç¬à¬Õ¬Ú¬Þ
	do
		if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) // ¬Ö¬ã¬Ý¬Ú ¬Þ¬í ¬ß¬Ñ¬ê¬Ý¬Ú ¬æ¬Ñ¬Û¬Ý
		{
			char file[MAX_PATH];
			if (GetFullPathName(lpszFileName, MAX_PATH, file, &part) == 0) return FALSE;
			strcpy(part, wfd.cFileName);

			lpSearchFunc(file);
		}
	while (FindNextFile(hSearch, &wfd)); // ¬Ú¬ë¬Ö¬Þ ¬ã¬Ý¬Ö¬Õ¬å¬ð¬ë¬Ú¬Û ¬æ¬Ñ¬Û¬Ý
	FindClose(hSearch); // ¬Ù¬Ñ¬Ü¬Ñ¬ß¬é¬Ú¬Ó¬Ñ¬Ö¬Þ ¬á¬à¬Ú¬ã¬Ü

	return TRUE;
}

void showstartparams()
{
	printf("Use: DataParser [-t] <filename> or <all>\n");
	printf("\t-t\t Online Translate\n");
	fprintf(fLog, "Use: DataParser [-t] <filename> or <all>\n\n");
	fprintf(fLog, "\t-t\t Online Translate\n");
	exit(0);
}

//=================================================================================
// Îñíîâíàÿ ôóíêöèÿ
//
int _tmain(int argc, _TCHAR* argv[])
{	
	int as = 28526;
	float fs;
	fs = *((float*)(&as));
	translate = false;
//	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	fLog = fopen("./result.log", "a+");
	if (fLog == NULL)
	{
		printf("Can't create log file\n");
		return -1;
	}

	fprintf(fLog, "#######################################\n");
	fprintf(fLog, "# BIN File Parser (ver: 1.00)         #\n");
	fprintf(fLog, "# Authors: Tahoma                     #\n");
	fprintf(fLog, "#######################################\n\n");
	
	
	if (argc < 2)
		showstartparams();
	
	strcpy(filename, argv[1]);

	if (strlen(filename) < 2)
		showstartparams();

	if (filename[0] == '-')
	{
		switch (filename[1])
		{
		case 't':
			translate = true;
			break;
		}

		strcpy(filename, argv[2]);
	}

	if (strlen(filename) < 2)
		showstartparams();


	if (!(strcmp(filename, "all")))
	{
		SearchFiles("*.bin", DoSomething, false);
		return 0;
	}

	if (!CreateResultFile(filename))
	{
		fprintf(fLog, "Can't create result file.\n");
		return -1;
	}

	freal = fopen(filename, "rb");
	if (!filename)
	{
		printf("Can't open file %s\n\n", filename);
		fprintf(fLog, "Can't open file %s\n\n", filename);
		return -1;
	}

	printf("File: %s:\n", short_filename);
	fprintf(fLog, "File: %s:\n", short_filename);

	Parser();
	return 0;
}
