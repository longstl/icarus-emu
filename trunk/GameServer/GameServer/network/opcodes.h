////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _OPCODES_H_
#define _OPCODES_H_

//////////////////////////////////////////////////////////////////////
// OPCODES ///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#define OPCODE_CM_CONNECT						0x010e		// 
#define OPCODE_SM_UNK1							0x440e		// 
#define OPCODE_SM_CONNECT						0x020e		// 
#define OPCODE_SM_UNK4							0xfe0e		// 
#define OPCODE_CM_DISCONNECT					0xfa0e		// 
#define OPCODE_SM_DISCONNECT					0xfb0e		// 
#define OPCODE_CM_UNK2							0xfd0e		// 
#define OPCODE_CM_GETAREA						0x320e		//
#define OPCODE_CM_UNK4							0x3c0e		// 
#define OPCODE_SM_UNK7							0x3d0e		// 
#define OPCODE_CM_UNK5							0x460e		// 
#define OPCODE_SM_UNK8							0x470e		// 
#define OPCODE_CM_QUESTLIST						0x390e		// 
#define OPCODE_SM_QUESTLIST						0x3a0e		// 
#define OPCODE_SM_SETAREA						0x330e		// 
#define OPCODE_SM_UNK5							0x230f		// 
#define OPCODE_SM_UNK3							0x8c0f		// 
#define OPCODE_CM_UNK6							0x8d0e		// 
#define OPCODE_SM_UNK9							0x8e0e		// 
#define OPCODE_CM_UNK7							0x900e		// 
#define OPCODE_SM_UNK10							0x910e		// 
#define OPCODE_CM_UNK8							0xd20e		// 
#define OPCODE_SM_UNK11							0xd30e		// 
#define OPCODE_SM_UNK12							0x350e		// 
#define OPCODE_SM_UNK13							0x053d		// 

#define OPCODE_CM_UNK9							0xcb0e		// 
#define OPCODE_SM_UNK14							0xcc0e		// 
#define OPCODE_SM_UNK15							0xcd0e		// 
#define OPCODE_CM_UNK10							0x970e		// 
#define OPCODE_SM_UNK16							0x980e		// 
#define OPCODE_CM_UNK11							0xa00e		// 
#define OPCODE_SM_UNK17							0xa10e		// 
#define OPCODE_CM_UNK12							0x640e		// 
#define OPCODE_SM_UNK18							0x650e		// 
#define OPCODE_CM_UNK13							0x291d		// 
#define OPCODE_CM_UNK14							0x013d		// 
#define OPCODE_CM_UNK15							0x4e0e		// 
#define OPCODE_CM_UNK16							0x340e		// 
#define OPCODE_CM_UNK17							0x0a2b		// 
#define OPCODE_CM_UNK18							0x360e		// 
#define OPCODE_CM_UNK19							0x410e		// 
#define OPCODE_CM_UNK20							0x3f0e		// 
#define OPCODE_CM_UNK21							0x4a0e		// 
#define OPCODE_CM_UNK22							0x0127		// 
#define OPCODE_CM_UNK23							0x600e		// 
#define OPCODE_CM_UNK24							0x620e		// 
#define OPCODE_CM_UNK25							0x1406		// 
#define OPCODE_CM_UNK26							0x2013		// 
#define OPCODE_CM_UNK27							0x013c		// 
#define OPCODE_CM_UNK28							0x013e		// 
#define OPCODE_SM_UNK23							0x013f		// 
#define OPCODE_CM_UNK29							0x1f10		// 

#define OPCODE_SM_ENTER_WORLD					0x010f		// 
#define OPCODE_SM_UNK20							0x020f		// 
#define OPCODE_SM_UNK21							0x030f		// 
#define OPCODE_SM_GAMEOBJECT_SPAWN				0x1b10		// 
#define OPCODE_SM_UNK24							0xd50e		// 
#define OPCODE_SM_UNK25							0x2018		// 
#define OPCODE_SM_UNK26							0x2318		// 
#define OPCODE_SM_UNK27							0x3218		// 
#define OPCODE_SM_UNK28							0x210f		// 
#define OPCODE_SM_UNK29							0x033f		//
#define OPCODE_SM_UNK30							0x2a1d		//
#define OPCODE_SM_UNK31							0x2b1d		//
#define OPCODE_SM_UNK32							0x033d		//
#define OPCODE_SM_UNK33							0xa113		//
#define OPCODE_SM_UNK34							0x043d		//
#define OPCODE_SM_UNK35							0x9b13		//
#define OPCODE_SM_UNK36							0x023d		//
#define OPCODE_SM_MESSAGE						0x0310		//
#define OPCODE_SM_UNK38							0xf30e		//
#define OPCODE_SM_UNK39							0x4c0e		//
#define OPCODE_SM_UNK40							0x9913		//
#define OPCODE_SM_UNK_610e						0x610e		//
#define OPCODE_SM_UNK_0227						0x0227		//
#define OPCODE_SM_UNK_380e						0x380e		//

#define OPCODE_CM_UNK_6e0e						0x6e0e		//
#define OPCODE_SM_UNK_6f0e						0x6f0e		//

#define OPCODE_CM_UNK_5120						0x5120		//

#define OPCODE_CM_CHAT							0x0111		// 

// SYSTEM
#define OPCODE_CM_PING							0x0165		// ok
#define OPCODE_SM_PONG							0x0165		// ok


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////


#include "inc_opcodes.h"


bool LSOpcodes(PACKET* pck)
{
	char bindbg[2];

	switch (pck->opcode)
	{
		OPCODE(OPCODE_CM_PING, CM_PING);
		OPCODE(OPCODE_CM_CONNECT, CM_CONNECT);
		OPCODE(OPCODE_CM_DISCONNECT, CM_DISCONNECT);
		OPCODE(OPCODE_CM_UNK2, CM_UNK2);
		OPCODE(OPCODE_CM_GETAREA, CM_GETAREA);
		OPCODE(OPCODE_CM_UNK4, CM_UNK4);
		OPCODE(OPCODE_CM_UNK5, CM_UNK5);
		OPCODE(OPCODE_CM_UNK6, CM_UNK6);
		OPCODE(OPCODE_CM_UNK7, CM_UNK7);
		OPCODE(OPCODE_CM_UNK8, CM_UNK8);
		OPCODE(OPCODE_CM_UNK9, CM_UNK9);
		OPCODE(OPCODE_CM_UNK10, CM_UNK10);
		OPCODE(OPCODE_CM_UNK11, CM_UNK11);
		OPCODE(OPCODE_CM_UNK12, CM_UNK12);
		OPCODE(OPCODE_CM_UNK13, CM_UNK13);
		OPCODE(OPCODE_CM_UNK14, CM_UNK14);
		OPCODE(OPCODE_CM_UNK15, CM_UNK15);
		OPCODE(OPCODE_CM_UNK16, CM_UNK16);
		OPCODE(OPCODE_CM_UNK17, CM_UNK17);
		OPCODE(OPCODE_CM_UNK18, CM_UNK18);
		OPCODE(OPCODE_CM_UNK19, CM_UNK19);
		OPCODE(OPCODE_CM_UNK20, CM_UNK20);
		OPCODE(OPCODE_CM_UNK21, CM_UNK21);
		OPCODE(OPCODE_CM_UNK22, CM_UNK22);
		OPCODE(OPCODE_CM_UNK23, CM_UNK23);
		OPCODE(OPCODE_CM_UNK24, CM_UNK24);
		OPCODE(OPCODE_CM_UNK25, CM_UNK25);
		OPCODE(OPCODE_CM_UNK26, CM_UNK26);
		OPCODE(OPCODE_CM_UNK27, CM_UNK27);
		OPCODE(OPCODE_CM_UNK28, CM_UNK28);
		OPCODE(OPCODE_CM_UNK29, CM_UNK29);
		OPCODE(OPCODE_CM_UNK_6e0e, CM_UNK_6e0e);
		OPCODE(OPCODE_CM_UNK_5120, CM_UNK_5120);

		OPCODE(OPCODE_CM_QUESTLIST, CM_QUESTLIST);
		//		OPCODE(OPCODE_CM_DISCONNECT, CM_DISCONNECT);
		OPCODE(OPCODE_CM_CHAT, CM_CHAT);


		
		
		default:
		{
			// DEBUG
			memset(bindbg, 0, 2);
			char* fordebug = pck->GetPacketPointer();
			log::Debug(fg, "C->S: op[%04x][%02x] ", pck->opcode, pck->real_packet_size);
			for (uint16 i = 0; i < (uint16)pck->packet_len; i++)
			{
				if ((uint8)fordebug[i] > 0x20 && (uint8)fordebug[i] <= 'z')
				{
					bindbg[0] = (uint8)fordebug[i];
					log::Notify(fg, bindbg);
				}
				else
					log::Notify(fg, ".");
			}
			log::Notify(fg, "\n");

			log::Debug(fg, "C->S: op[%04x][%02x] ", pck->opcode, pck->real_packet_size);
			for (uint16 i = 0; i < (uint16)pck->packet_len; i++)
				log::Notify(fg, "%02x", (uint8)fordebug[i]);

			log::Notify(fg, "\n");
			// --DEBUG
		}
		

	}
	return true;
}

void opcodes(PACKET* pck)
{
	pck->PackCreate();

	if (!LSOpcodes(pck))
	{

	}
}

#endif _OPCODES_H_


