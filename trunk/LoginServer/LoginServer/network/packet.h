////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _PACKET_H_
#define _PACKET_H_

#include <Windows.h>
#include <stdio.h>
#include "../defines.h"
#include "../structs.h"
#include "../common/logger.h"


#define PACKET_LEN	1024*64

class PACKET
{
public:
	PACKET(THREAD_STRUCT* sockstruct);
	~PACKET();
	bool PackRecv();								/*-- �������� ����? ���������� ����??opcode, ���������� ������ ������ ?real_packet_size ?����������?��������??compress */
	void PackCreate();								/* ������������ ������ ��� �������� ������ */
	bool PackSend(uint16 op);						/* ��������� ��������??������?�� ����?*/
	void CreateBufForSend();						/* ������?����?��� ������?����?������ */
	void drop();									/* ������� ���������� ?������ */
	void Disconnect();								/* ���Ѭ٬��ӬѬ֬� ���լܬݬ��֬߬ڬ�*/

	int					packet_len;					/* ������ ������ ?������?*/
	uint16				opcode;
	uint16				real_packet_size;
	bool				compress;
	char				packet_buf[PACKET_LEN];
	char*				GetPacketPointer();			/* ���������� ��������?�� ����?������ ������? �������� */
	THREAD_STRUCT*		sockstruct;
	bool				isconnected;

private:	
	int					_packet_len;
	uint32				size_new_packet;
	char*				buf_use_packed;
	uint32				offset;
	uint32				offset_snd;
	char				packet_snd[PACKET_LEN];
	FILE*				fg;
	
public:
	template <typename T> T read()
	{
		try
		{
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

	// ��������? UNICODE ������ ?���������� ����??���������� ����?
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

	// ��������? ������ ?���������� ����??���������� ����?
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

	// ��������? UNICODE ������ ?����?��� ������?������
	int writeUstr(WCHAR* wc)
	{
		int lenwc = wcslen(wc);
		memcpy(packet_snd + offset_snd, wc, lenwc * 2 + 2);
		offset_snd += lenwc*2+2;
		return lenwc;
	}

	// ��������? ������ ?����?��� ������?������
	int writeTstr(TCHAR* tc)
	{
		int lentc = strlen(tc);
		memcpy(packet_snd + offset_snd, tc, lentc+1);
		offset_snd += lentc+1;
		return lentc;
	}

	//====================================================================================
	// ��������? ��������?����??����?������ ��� ������?������
	//
	int writeBuf(TCHAR* tc, int len)
	{
		memcpy(packet_snd + offset_snd, tc, len);
		offset_snd += len;
		return len;
	}
};

#endif _PACKET_H_