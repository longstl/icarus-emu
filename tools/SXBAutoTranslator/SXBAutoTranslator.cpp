////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////
#include "stdafx.h"
#include "SXBAutoTranslator.h"

typedef void(*LPSEARCHFUNC)(LPCTSTR lpszFileName);

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
//			SendMessage(hTranslate, WM_SETTEXT, NULL, (LPARAM)tmp);
			break;
		}
	}
	return size*nmemb;
}

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
//		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
			MessageBox(NULL, "curl_easy_perform() failed: \n", curl_easy_strerror(res), NULL);		
		}
		curl_easy_cleanup(curl);
	}
}

//=================================================================================
// Create BAK file
//
void CreateBackupFile(char* filename)
{
	int filesize;
	char bak_filename[256];
	sprintf(bak_filename, "%s.bak", filename);
	FILE* freal = fopen(filename, "rb");
	FILE* fbak = fopen(bak_filename, "wb");
	fseek(freal, 0, SEEK_END);
	filesize = ftell(freal);
	fseek(freal, 0, SEEK_SET);

	void *buf = malloc(filesize);
	fread(buf, filesize, 1, freal);
	fwrite(buf, filesize, 1, fbak);
	free(buf);

	fclose(freal);
	fclose(fbak);
}

//=================================================================================
// Save SXB file
//
void WriteSXBFile(char* filename)
{
	char nul[] = "\0\0";

	CreateBackupFile(filename);
	FILE* fl = fopen(filename, "wb");
	fwrite((void*)&num_head_elements, 2, 1, fl);

	for (int i = 0; i < num_head_elements; i++)
	{
		fwrite((void*)&hd_elements[i].head_elem_num, 1, 1, fl);
		fwrite((void*)&hd_elements[i].head_elem_size, 1, 1, fl);
		fwrite((void*)&hd_elements[i].head_elem_txt, hd_elements[i].head_elem_size, 1, fl);
	}

	int nnn = num_elements;
	fwrite((void*)&nnn, 2, 1, fl);

	int step = 0;

	for (int i = 0; i < num_elements; i++)
	{
		for (int y = 0; y < num_head_elements; y++)
		{
			fwrite((void*)&step, 4, 1, fl);
			step += wcslen(elmdata[i].dat[y]) + 1;
		}
	}
	int len_datas = step * 2;
	fwrite((void*)&len_datas, 4, 1, fl);

	for (int i = 0; i < num_elements; i++)
	{
		for (int y = 0; y < num_head_elements; ++y)
		{
			fwrite(elmdata[i].dat[y], wcslen(elmdata[i].dat[y]) * 2 + 2, 1, fl);
		}
	}
	fclose(fl);
}

//=================================================================================
// Open SXB file
//
void OpenSXBFile(char* filename)
{
	char msg[1024];

	hSXB = fopen(filename, "rb");
	if (hSXB != NULL)
	{
		fseek(hSXB, 0, SEEK_END);
		int size = ftell(hSXB);
		fseek(hSXB, 0, SEEK_SET);

		fread((void*)&num_head_elements, 2, 1, hSXB);
		for (int i = 0; i < num_head_elements; i++)
		{
			memset((void*)&hd_elements[i].head_elem_txt, 0, 32);
			fread((void*)&hd_elements[i].head_elem_num, 1, 1, hSXB);
			fread((void*)&hd_elements[i].head_elem_size, 1, 1, hSXB);
			fread((void*)&hd_elements[i].head_elem_txt, hd_elements[i].head_elem_size, 1, hSXB);
		}

		fread((void*)&num_elements, 2, 1, hSXB);

		elm = new ELEMENT[num_elements];
		for (int y = 0; y < num_elements; y++)
		{
			for (int i = 0; i < num_head_elements; i++)
			{
				fread((void*)&elm[y].step[i], 4, 1, hSXB);
			}
		}

		fread((void*)&all_elements_size, 4, 1, hSXB);
		data_step = ftell(hSXB);

		elmdata = new ELMDATA[num_elements];
		for (int i = 0; i < (num_elements); i++)
		{
			fseek(hSXB, elm[i].step[0] * 2 + data_step, SEEK_SET);
			fread(elmdata[i].dat[0], 1024 * 2, 1, hSXB);
			fseek(hSXB, elm[i].step[1] * 2 + data_step, SEEK_SET);
			fread(elmdata[i].dat[1], 1024 * 2, 1, hSXB);

			for (int y = 2; y < num_head_elements; y++)
			{
				memset(elmdata[i].dat[y], 0, 1024 * 2);
//				fseek(hSXB, elm[i].step[y] * 2 + data_step, SEEK_SET);
	//			fread(elmdata[i].dat[y], 1024 * 2, 1, hSXB);
			}
		}
	}
	else
	{
		sprintf(msg, "Can't open file: %s\n", filename);
		printf(msg);
		exit(0);
	}
}

void AutoTranslate(char* filename)
{	
	isoldselected = -1;
	hSXB = NULL;
	elm = NULL;
	elmdata = NULL;
	size_t convertedChars = 0;
	WCHAR tmp[1024];
	char msg[1024];
	int len_element_name = 0;
	num_elements = 0;

	// open
	OpenSXBFile(filename);
	// translate
	for (int i = 0; i < num_elements; i++)
	{
		if (i == 277)
		{
			tmp[0] = tmp[0];
		}
		Translat(elmdata[i].dat[1]);
		int size_str = strlen(tmp_translate);
		if (size_str == 0)
		{
			__ERROR;
			printf("Error on position: %d\n", i);
			fprintf(fr, "Error on position: %d\n", i);
			__INFO;
			return;
		}

		len_element_name = wcstombs(msg, elmdata[i].dat[0], 1024);
		__INFO;
		printf("N:");
		fprintf(fr, "N:");
		__WARNING;
		printf("%d ", i);
		fprintf(fr, "%d\t", i);
		__INFO;
		printf("D: ");
		fprintf(fr, "D: ");
		__WARNING;
		printf("%s ", msg);
		fprintf(fr, "%s\t", msg);
		__INFO;
		printf("T: ");
		fprintf(fr, "T: ");
		__WARNING;
		printf("%s\n", tmp_translate);
		fprintf(fr, "%s\n", tmp_translate);
		memset(tmp, 0, sizeof(tmp));
		mbstowcs_s(&convertedChars, tmp, size_str + 1, tmp_translate, _TRUNCATE);
		wcscpy(elmdata[i].dat[1], tmp);
	}

	// save
	WriteSXBFile(filename);

	if (elm != NULL)
		delete(elm);

	if (elmdata != NULL)
		delete (elmdata);
}

void DoSomething(LPCTSTR lpszFileName)
{
	__FILE;
	printf("\n\n\n\nFile: %s\n", lpszFileName);
	fprintf(fr, "\n\n\n\nFile: %s\n", lpszFileName);
	AutoTranslate((char*)lpszFileName);
	__INFO;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// error: localstringdata_dialog.sxb
	char filename[256];
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	fr = fopen("./result.txt", "wb");
	if (fr == NULL)
	{
		__ERROR;
		printf("Can't create result file\n");
		__INFO;
		return -1;
	}

	__WARNING
	printf("#########################################\n");
	printf("# SXB Files Auto Translator (ver: 1.00) #\n");
	printf("# Authors: Tahoma                       #\n");
	printf("#########################################\n\n");
	__INFO;

	if (argc < 2)
	{
		printf("Use: SXBAutoTranslator <filename> or <all>\n\n");
		return -1;
	}

	if (!(strcmp(argv[1], "all")))
	{
		SearchFiles("*.sxb", DoSomething, false);
		return 0;
	}

	strcpy(filename, argv[1]);
	AutoTranslate(argv[1]);

	return 0;
}

