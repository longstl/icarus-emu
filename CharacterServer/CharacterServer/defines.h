////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _DEFINES_H_
#define _DEFINES_H_

#define uint64		unsigned __int64
#define uint32		unsigned int
#define uint16		unsigned __int16
#define uint8		unsigned __int8

#define int64		__int64
#define int32		__int32
#define int16		__int16
#define int8		__int8

// For PACKET class
#define readUB		read<uint8>
#define readUW		read<uint16>
#define readUD		read<uint32>
#define readB		read<int8>
#define readW		read<int16>
#define readD		read<int32>

#define writeUB		write<uint8>
#define writeUW		write<uint16>
#define writeUD		write<uint32>
#define writeB		write<int8>
#define writeW		write<int16>
#define writeD		write<int32>

#endif _DEFINES_H_