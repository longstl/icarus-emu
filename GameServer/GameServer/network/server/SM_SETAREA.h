////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_SETAREA_H_
#define _SM_SETAREA_H_

void SM_SETAREA(PACKET* pck)
{
	pck->CreateBufForSend();
	pck->writeW(0);
	pck->writeD(0);
	pck->writeUD(pck->me->id);
	pck->writeBuf(pck->me->charname, 20);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeB(0);
	pck->writeB(0);
	pck->writeB(pck->me->cls);
	pck->writeB(pck->me->sex);
	pck->writeD(0x3bd70900);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeW(pck->me->lvl);
	pck->writeW(0);
	pck->writeD(0);
	pck->writeW(0);
	pck->writeB(0);
	pck->writeB(0);
	pck->writeB(13);
	pck->writeB(0);
	pck->writeW(0);
	pck->writeD(0);
	pck->writeD(0x443da004);		// pos_x
	pck->writeD(0x44608e38);		// pos_y
	pck->writeD(0x42001d80);		// pos_z
	pck->writeD(0x420c0000);		// rotate
	pck->writeD(0x18);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(0xffffffff);
	pck->writeD(0);
	pck->writeD(0);
	pck->writeD(0x3fcbd404);
	pck->writeD(1);
	pck->writeD(0x403b0640);
	pck->writeD(1);
	pck->writeD(0x3fcbaf54);
	pck->writeD(1);
	pck->writeD(0x3344f438);
	pck->writeD(1);
	pck->writeD(0x580973a0);
	pck->writeD(1);
	char area[] = "area_f01_p_0001";
	char tmp_area[24];
	memset(tmp_area, 0, 24);
	strcpy(tmp_area, area);
	pck->writeBuf(tmp_area, 24);
	pck->writeD(0x3f000000);
	pck->writeD(1);
	pck->PackSend(OPCODE_SM_SETAREA);
}

/*
e600
0e33
0000
00000000
9a832600 - id char

43006800750070006f006b006100620072006100
00000000
00000000
00000000
00000000
00000000
0082b744
00000000
00000000
01000000
00000000
00000000
0c0000000000000000003f43008058440000c4420000e4421800000000000000000000000000000000000000000000000000000000000000000000000000000000000000ffffffff0000000000000000
948fa23f
01000000
b0eb0f40
01000000
c467a23f
01000000
587a2667
01000000
a806a6a3
01000000
617265615f6630315f705f30303031000000000000000000
0000003f
01000000

0E33
0000
00000000
C7722700

5400610068006F006D0061003200000000000000
00000000
00000000
00000000
00000000
00
00
05
01
0009D73B
00000000
00000000

0100
0000
00000000
0000
00
00
0D
00
0000
00000000


04D03D44
388E6044
801D0042
00000C42
18000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
00000000
FFFFFFFF
00000000
00000000
04D4CB3F
01000000
40063B40
01000000
54AFCB3F
01000000
38F44433
01000000
A0730958
01000000
61 72 65 61 5F 66 30 31 5F 70 5F 30   ....area_f01_p_0
30 30 31 00 00 00 00 00 00 00 00 00 00 00 00 3F   001............?
01 00 00 00

*/

#endif
