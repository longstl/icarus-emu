////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#include "packet.h"

PACKET::PACKET(THREAD_STRUCT* sockstruct)
{
	this->sockstruct = sockstruct;
	this->sockstruct->send_serverlist = false;
	isconnected = true;
	buf_use_packed = 0;
	size_new_packet = 0;
	offset = 0;
	fg = sockstruct->fg;
}

PACKET::~PACKET()
{

}

void PACKET::Disconnect()
{
	closesocket(sockstruct->socket);
	sockstruct->socket = NULL;
	isconnected = false;
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

bool PACKET::PackRecv() 
{
	if ((packet_len = recv(sockstruct->socket, packet_buf, PACKET_LEN, 0)) == SOCKET_ERROR)
		return false;

	if (packet_len == 0)
	{
		Disconnect();
		return false;
	}

	int nError = WSAGetLastError();
	if (nError != WSAEWOULDBLOCK && nError != 0)
	{
		log::Error(fg, "PCKHandler: Recv packet error: %d \n", nError);
		Disconnect();
		return false;
	}

	offset = 0;
	buf_use_packed = packet_buf;

	real_packet_size = readUW();
	opcode = readUW();
	packet_len = real_packet_size - offset;		
	return true;
}

bool PACKET::PackSend(uint16 op)
{
	char pack[PACKET_LEN + 4];
	memcpy(pack + 4, packet_snd, offset_snd);

	uint16 pack_len = offset_snd + 4;
	memcpy(pack, &pack_len, 2);
	memcpy(pack + 2, &op, 2);
	send(sockstruct->socket, pack, pack_len, NULL);
	return true;
}
//////////////////////////////////////////////////////////////////////////
// Возвращает указател?на буфе?пакета учитыв? смещение
//////////////////////////////////////////////////////////////////////////
char* PACKET::GetPacketPointer()
{
	return buf_use_packed + offset;
}