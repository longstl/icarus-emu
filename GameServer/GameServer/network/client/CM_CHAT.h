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
		SM_UNK27(pck);
		break;
	case '2':
		break;
	case '3':
		SM_UNK_400e(pck);
		break;
	case '4':
		SM_UNK_2a0f(pck);
		break;
	case '5':
		SM_UNK_4b0e(pck);
		break;
	case '6':
		SM_UNK_4f0e(pck);
		break;
	case '7':
		SM_UNK_6f0e(pck);
		break;
	case '8':
		SM_UNK_9c13(pck);
		break;
	case '9':
		SM_UNK_9e13(pck);
		break;
	case 'a':
		SM_UNK_023c(pck);
		break;
	case 'b':		
		SM_UNK_023e(pck);
		break;
	case 'c':
		SM_UNK_033c(pck);
		break;
	case 'd':
		SM_UNK_033e(pck);
		break;
	case 'e':
		SM_UNK_0310(pck);
		break;
	case 'f':
		SM_UNK_0335(pck);
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