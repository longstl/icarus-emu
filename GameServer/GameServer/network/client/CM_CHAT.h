////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_CHAT_H_
#define _CM_CHAT_H_

inline void CM_CHAT(PACKET* pck)
{	
	char str[1024];
	int8 cryptflag = pck->readW();
	
	uint32 unk2 = pck->readD();
	uint32 unk3 = pck->readD();
	uint32 unk4 = pck->readD();
	uint32 unk5 = pck->readD();
	uint32 unk6 = pck->readD();
	uint32 unk7 = pck->readD();
	uint32 unk8 = pck->readD();
	uint32 unk9 = pck->readD();
	uint32 unk10 = pck->readD();
	uint32 unk11 = pck->readD();
	uint16 unk12 = pck->readW();
	int len = pck->read2Str(str);

	uint8 byte = str[0];
	switch (byte)
	{
	case '1':
		SM_UNK_0b2b(pck);
		SM_UNK_0c2b(pck);
		break;
	case '2':
		SM_UNK_400e(pck);
		break;
	case '3':
		SM_UNK_4b0e(pck);
		break;
	case '4':
		SM_UNK35(pck);
		break;
	case '5':
		break;
	case '6':
		break;
	case '7':
		break;
	case '8':
		break;
	case '9':
		break;
	case 'a':
		break;
	case 'b':		
		break;
	case 'c':
		break;
	case 'd':
		break;
	case 'e':
		break;
	case 'f':
		break;

	}
//	SM_CHAT(pck);
}

/*
1100 01AF
01000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
2498
1000
31313131313131313131313131313131   1111111111111111
0000                                             ..

*/

#endif