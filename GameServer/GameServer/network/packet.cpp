////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#include "packet.h"

PACKET::PACKET(SOCKET sock, CHARACTER* me, DATABASE* mysql, FILE* fg, int* pingtime)
{
	this->socket = sock;
	this->me = me;
	this->sql = mysql;
	this->fg = fg;
	this->pingtime = pingtime;
	isconndected = true;
	buf_use_packed = 0;
	size_new_packet = 0;
	offset = 0;
}

PACKET::~PACKET()
{

}

void PACKET::Disconnect()
{
	shutdown(socket, NULL);
	closesocket(socket);
	socket = NULL;
	isconndected = false;
}

void PACKET::CreateBufForSend()
{
	memset(packet_snd, 0, PACKET_LEN);
	offset_snd = 0;
}

void PACKET::PackCreate()
{
}

void PACKET::drop()
{
	packet_len = NULL;
}

//====================================================================================
// ���� � ����� ������ ���� ������ ������ ������, �� ������������
//
bool PACKET::NextPacket()
{
	offset = old_offset + old_packet_len;
	if (offset >= PACKET_LEN)
	{
		log::Error(fg, "PCK: buffer OEF.\n", packet_len, real_packet_size);
		return false;
	}

	old_offset = offset;

	real_packet_size = readUW();
	old_packet_len = real_packet_size;
	if (real_packet_size == 0)
		return false;

	opcode = readUW();
	int cryptflag = readB();
	--offset;

	if (real_packet_size < 4)
	{
		log::Error(fg, "PCKHandler: recv packet len: %d, in packet: %d\n", packet_len, real_packet_size);
		for (int i = 0; i < packet_len; i++)
		{
			log::Notify(fg, "%02x", (uint8)packet_buf[i]);
		}
		log::Notify(fg, "\n");
		return false;
	}

	packet_len = real_packet_size - 4;
	if (cryptflag == 1)
	{
		int step_xor_key = 0;
		char xor_key[] = { 0xb1, 0xe1, 0xd2, 0xc4, 0x4a, 0x2f, 0x6b, 0x22 };
		for (int i = 2; i < packet_len - 2; i++)
		{
			buf_use_packed[i + offset] ^= xor_key[step_xor_key];
			++step_xor_key;
			if (step_xor_key == sizeof(xor_key))
				step_xor_key = 0;
		}
	}
}

//====================================================================================
// ��������� ���������� �������� ������
//
bool PACKET::PackRecv() 
{
	memset(packet_buf, 0, PACKET_LEN-1);
	if ((packet_len = recv(socket, packet_buf, PACKET_LEN, 0)) == (uint16)SOCKET_ERROR)
	{
		return false;
	}
	if (packet_len == 0)
	{
		Disconnect();
		return false;
	}
		
	int nError = WSAGetLastError();
	if (nError != WSAEWOULDBLOCK && nError != 0)
	{
		Disconnect();
		return false;
	}

	offset = 0;
	old_offset = 0;
	buf_use_packed = packet_buf;

	real_packet_size = readUW();

	old_packet_len = real_packet_size;
	opcode = readUW();
	int cryptflag = readB();
	--offset;

	if (real_packet_size < 4)
	{
		log::Error(fg, "PCKHandler: recv packet len: %d, in packet: %d\n", packet_len, real_packet_size);
		for (int i = 0; i < packet_len; i++)
		{
			log::Notify(fg, "%02x", (uint8)packet_buf[i]);
		}
		log::Notify(fg, "\n");
		return false;
	}

	packet_len = real_packet_size - offset;

	if (cryptflag == 1)
	{
		int step_xor_key = 0;
		char xor_key[] = { 0xb1, 0xe1, 0xd2, 0xc4, 0x4a, 0x2f, 0x6b, 0x22 };
		for (int i = 2; i < packet_len-2; i++)
		{
			buf_use_packed[i + offset] ^= xor_key[step_xor_key];
			++step_xor_key;
			if (step_xor_key == sizeof(xor_key))
				step_xor_key = 0;
		}
	}

	return true;
}

bool PACKET::PackSend(uint16 op)
{
	char pack[PACKET_LEN + 4];
	memcpy(pack + 4, packet_snd, offset_snd);

	uint16 pack_len = offset_snd + 4;
	memcpy(pack, &pack_len, 2);
	memcpy(pack + 2, &op, 2);

	/// DEBUG
	char tmp[2];
	tmp[1] = 0;
	log::Debug(fg, "S->C: op[%04x] ", op);
	for (int i = 4; i < pack_len; i++)
	{
		if ((uint8)pack[i] > 0x20 && (uint8)pack[i] <= 'z')
		{
			tmp[0] = (uint8)pack[i];
			log::Notify(fg, tmp);
		}
		else
		{
			log::Notify(fg, ".");
		}
	}
	log::Notify(fg, "\n");
	log::Debug(fg, "S->C: op[%04x] ", op);
	for (int i = 4; i < pack_len; i++)
	{
		log::Notify(fg, "%02x", (uint8)pack[i]);
	}
	log::Notify(fg, "\n");
	/// !DEBUG

	int s = send(socket, pack, pack_len, NULL);
	int nError = WSAGetLastError();
	if (nError != WSAEWOULDBLOCK && nError != 0)
	{
		Disconnect();
		return false;
	}
	return true;
}

//====================================================================================
// Get pointer in packet
//
char* PACKET::GetPacketPointer()
{
	return buf_use_packed + offset;
}