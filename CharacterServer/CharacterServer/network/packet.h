////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _PACKET_H_
#define _PACKET_H_

#include <Windows.h>
#include <stdio.h>
#include <assert.h>
#include "../defines.h"
#include "../structs.h"
#include "../common/logger.h"
#include "../common/database.h"

#define account		pck->sockstruct
#define PACKET_LEN	1024*64

class PACKET
{
public:
	PACKET(THREAD_STRUCT* sockstruct, int max_characters);
	~PACKET();
	bool PackRecv();								/*-- �������� ����? ���������� ����??opcode, ���������� ������ ������ ?real_packet_size ?����������?��������??compress */
	void PackCreate();								/* ������������ ������ ��� �������� ������ */
	bool PackSend(uint16 op);						/* ��������� ��������??������?�� ����?*/
	void CreateBufForSend();						/* ������?����?��� ������?����?������ */
	void drop();									/* ������� ���������� ?������ */
	void Disconnect();								/* ���Ѭ٬��ӬѬ֬� ���լܬݬ��֬߬ڬ�*/

	int					packet_len;					/* realno poluchennaya dlina paketa */
	uint16				opcode;
	uint16				real_packet_size;
	bool				compress;
	char				packet_buf[PACKET_LEN];
	char*				GetPacketPointer();			/* ���������� ��������?�� ����?������ ������? �������� */
	THREAD_STRUCT*		sockstruct;
	DATABASE*			sql;						/* ���ܬѬ٬Ѭ�֬ݬ� �߬� �ܬݬѬ�� �լݬ� ��ѬҬ��� �� ���� */
	bool				isconndecred;
	int					max_characters;

private:	
	int					_packet_len;
	uint32				size_new_packet;
	char*				buf_use_packed;
	uint32				offset;
	uint32				offset_snd;
	char				packet_snd[PACKET_LEN];
	FILE*				fg;
	int					cryptflag;
	
public:
	template <typename T> T read()
	{
		try
		{
			assert((offset + sizeof(T)) <= PACKET_LEN);
			T ret = *(reinterpret_cast<T*>(&buf_use_packed[offset]));

			offset += sizeof(T);
			return ret;
		}
		catch (char* msg)
		{
			log::Error(fg, "[ERROR] Error at reading. ErrorMsg: %s \n", msg);
			return NULL;
		}
	}

	//====================================================================================
	// ���ڬ�Ѭ֬� ��߬ڬܬ�� �����ܬ� �� ��ܬѬ٬Ѭ߬߬�� �Ҭ��֬�
	//
	int readWstr(WCHAR* wc)
	{
		int step = 0;
		for (int i = offset; i < packet_len; i += 2)
		{
			step += 2;
			if (buf_use_packed[i] == 0)
				break;			
		}

		memcpy(wc, &buf_use_packed[offset], step);
		offset += step;
		return step / 2;
	}

	//====================================================================================
	// ���ڬ�Ѭ֬� �����ܬ� �� ��ܬѬ٬Ѭ߬߬�� �Ҭ��֬�
	//
	int readTstr(TCHAR* tc)
	{
		int step = 0;
		for (int i = 0; i < real_packet_size; i++)
		{
			++step;
			if ((uint8)buf_use_packed[offset+i] == 0)
				break;			
		}

		memcpy(tc, &buf_use_packed[offset], step);
		offset += step;
		return step;
	}

	//====================================================================================
	// ���ڬ�Ѭ֬� ��ܬѬ٬Ѭ߬߬�� �ܬ�ݬڬ�֬��Ӭ� ��ڬެӬ�ݬ�� �� �٬Ѭ�ڬ��ӬѬ֬� �� �Ҭ��֬�
	//
	int readBuf(char* buf, int len)
	{
		assert((offset + len) <= PACKET_LEN);
		memcpy(buf, buf_use_packed + offset, len);
		offset += len;
		return len;
	}

	//====================================================================================
	// ���Ѭ�ڬ��ӬѬ֬� ��֬�֬ެ֬߬߬�� ��ܬѬ٬Ѭ߬߬�Ԭ� ��Ѭ٬ެ֬�� �� ���٬լѬӬѬ֬ެ�� ��Ѭܬ֬�
	//
	template <typename T> void write(T newData)
	{
		try
		{
			assert((offset_snd + sizeof(T)) <= PACKET_LEN);
			memcpy(&packet_snd[offset_snd], reinterpret_cast<uint8*>(&newData), sizeof(newData));

			offset_snd += sizeof(newData);
		}
		catch (char* msg)
		{
			log::Error(fg, "[ERROR] Error at writing. ErrorMsg: %s \n", msg);
		}
	}

	//====================================================================================
	// ���Ѭ�ڬ��ӬѬ֬� ��߬ڬܬ�� �����ܬ� �� ���٬լѬӬѬ֬ެ�� ��Ѭܬ֬�
	//
	int writeUstr(WCHAR* wc)
	{
		try
		{
			assert((offset_snd + (wcslen(wc)*2+2)) <= PACKET_LEN);
			int lenwc = wcslen(wc);
			memcpy(packet_snd + offset_snd, wc, lenwc * 2 + 2);
			offset_snd += lenwc*2+2;
			return lenwc;
		}
		catch (char* msg)
		{
			log::Error(fg, "[ERROR] Error at writing. ErrorMsg: %s \n", msg);
		}
	}

	//====================================================================================
	// ���Ѭ�ڬ��ӬѬ֬� �����ܬ� �� ���٬լѬӬѬ֬ެ�� ��Ѭܬ֬�
	//
	int writeTstr(TCHAR* tc)
	{
		int lentc = strlen(tc);
		memcpy(packet_snd + offset_snd, tc, lentc+1);
		offset_snd += lentc+1;
		return lentc;
	}

	//====================================================================================
	// ���Ѭ�ڬ��ӬѬ֬� �Ҭ��֬� �٬ѬլѬ߬߬�Ԭ� ��Ѭ٬ެ֬�� �� ���٬լѬӬѬ֬ެ�� ��Ѭܬ֬�
	//
	int writeBuf(void* tc, int len)
	{
		memcpy(packet_snd + offset_snd, tc, len);
		offset_snd += len;
		return len;
	}

	void writeA(char* in)
	{
		uint8 res;
		char tmp[3];
		memset(tmp, 0, 3);

		for (int i = 0; i < (int)strlen(in); i += 2)
		{
			strncpy(tmp, in + i, 2);
			res = (uint8)strtol(tmp, NULL, 16);
			memcpy(&packet_snd[offset_snd], reinterpret_cast<uint8*>(&res), sizeof(res));
			++offset_snd;
		}
	}
};

#endif _PACKET_H_