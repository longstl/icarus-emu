////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_CREATECHARACTER_H_
#define _CM_CREATECHARACTER_H_

void CM_CREATECHARACTER(PACKET* pck)
{
	CHAR_STYLE st;
	WCHAR w_charname[10];
	int len_character_name = pck->readBuf((char*)w_charname, 20);
	uint32 unk2 = pck->readUD();
	uint32 unk3 = pck->readUD();
	uint32 unk4 = pck->readUD();
	uint32 unk5 = pck->readUD();
	uint32 unk6 = pck->readUW();
	uint8 cls = pck->readUB();			// �ܬݬѬ��
	uint8 sex = pck->readUB();			// ����
	int16 unk71 = pck->readW();
	st.unk81 = 0;
	st.unk0 = pck->readUW();
	st.unk1 = pck->readUD();
	st.eye = pck->readUB();				// ����ެ� �ԬݬѬ�
	st.unk2 = pck->readUB();
	st.eyebrows = pck->readUB();		// �Ҭ��Ӭ�
	st.unk3 = pck->readUB();
	st.iris = pck->readUB();			// �٬�Ѭ�֬�
	st.unk4 = pck->readUW();
	st.unk5 = pck->readUB();
	st.tatoo = pck->readUB();			// ��Ѭ��
	st.unk6 = pck->readUW();
	st.unk7 = pck->readUB();
	st.unk8 = pck->readUW();			// 0x0000
	st.unk9 = pck->readUD();			// 0xffffffff
	st.hair = pck->readUB();			// ���ڬ�֬�ܬ�
	st.unk10 = pck->readUW();
	st.unk11 = pck->readUB();
	st.unk12 = pck->readUD();			// 0xffffffff
	st.unk13 = pck->readUD();
	st.unk14 = pck->readUD();
	st.color_lips = pck->readUD();		// ��Ӭ֬� �Ԭ��
	st.color_eyeb = pck->readUD();		// ��Ӭ֬� �Ҭ֬ݬܬ�
	st.color_iris = pck->readUD();		// ��Ӭ֬� ��Ѭլ�جܬ�
	st.color_eyebrows = pck->readUD();	// ��Ӭ֬� �Ҭ��Ӭ֬�
	st.color_eye = pck->readUD();		// ��Ӭ֬� �ԬݬѬ�
	st.unk15 = pck->readUD();
	st.unk16 = pck->readUD();
	st.unk17 = pck->readUD();
	st.unk18 = pck->readUD();
	st.unk19 = pck->readUD();
	st.unk20 = pck->readUD();
	st.unk21 = pck->readUD();
	st.unk22 = pck->readUD();
	st.unk23 = pck->readUD();
	st.unk24 = pck->readUD();
	st.unk25 = pck->readUD();
	st.unk26 = pck->readUD();
	st.unk27 = pck->readUD();
	st.unk28 = pck->readUD();
	st.unk29 = pck->readUD();
	st.unk30 = pck->readUD();
	st.unk31 = pck->readUD();
	st.unk32 = pck->readUD();
	st.unk33 = pck->readUD();
	st.unk34 = pck->readUB();
	st.unk35 = pck->readUB();
	st.unk36 = pck->readUB();
//	st.unk35 = pck->readUD();
//	st.unk36 = pck->readUD();
//	st.unk37 = pck->readUD();

	char charname[18];
	int len_charname = wcstombs(charname, w_charname, 18);
	if (len_charname < 4 || len_charname > 16)
	{
		SM_LOBBYUSERMSG(pck, 14);					// 
		return;
	}

	if (!(pck->sql->CheckCharname(charname)))
	{
		SM_LOBBYUSERMSG(pck, 14);					// !!!!!
		return;
	}

	int character_id = pck->sql->CreateCharacter(charname, &st, sex, cls, pck->sockstruct->account_id);

	SM_CREATECHARACTER(pck, character_id, charname, w_charname, cls, sex, &st);
}

#endif

/*
..T.a.h.o.m.a.......o............w...........>.2.*.'.6.:..iB..............pp......>>......!$(.....................?..................................................................Cp.....?....;
[021b]
5400610068006f006d0061000000 - nick
a802c0f5 +
6f09c897 + 
17000300 +
0000a0d5 +
0177f497 +
1700bcbb +
01       +
00		 +
00b1 +
813ec932 +
f9       + ����ެ� �ԬݬѬ�
2a       +
11       + �Ҭ��Ӭ�
27       +
b1       + �٬�Ѭ�֬�
3699     +
3a       +
e1       + ��Ѭ��
2e69     +
42       +
0000     +
ffffffff +
ec       + ���ڬ�֬�ܬ�
ff13     +
00       +
ffffffff +
707099ff +
d4d4d4ff +
3e3e82ff + ��Ӭ֬� �Ԭ�� 
ffffffff + ��Ӭ֬� �Ҭ֬ݬܬ�
212428ff + ��Ӭ֬� ��Ѭլ�جܬ�
000000ff + ��Ӭ֬� �Ҭ��Ӭ֬�
000000ff + ��Ӭ֬� �ԬݬѬ�
000000ff
ffffffff
ffffffff
3f
00 // ��Ѭ٬ެ֬� �Ԭ�ݬ�Ӭ�
00 // �����
00 // ��Ѭ٬ެ֬� ��֬�
00 // �լݬڬ߬� ��֬�
00 // ��ڬ�ڬ߬� �Ԭ��լ�
00 // ��Ѭ٬ެ֬� �Ԭ��լ�
00 // ��ڬ�ڬ߬� �جڬӬ���
00 // �Ӭ����� �جڬӬ���
00 // ��ڬ�ڬ߬� ��Ѭݬڬ�
00 // ��ڬ�ڬ߬� ��ݬ֬�
00 // ��Ѭ٬ެ֬� ��ݬ֬�֬ݬ��֬Ӭ�� �ެ����
00 // �լݬڬ߬� ��ݬ֬�֬ݬ��֬Ӭ�� �ެ����
00 // �լݬڬ߬� �ܬڬ���
00 // ���ݬ�ڬ߬� �ݬ��֬�
00 // ���ݬ�ڬ߬� �ڬܬ�
d8 // �լݬڬ߬� �߬��
00 // ���ݬ�ڬ߬� �����߬֬�
00 // ��ݬ�ج֬߬ڬ� ��֬ݬ� (���լ��ѬӬ�� - ���ݬ����)
00 // ��ܬ�ݬ�
00 // ��ܬ��Ԭݬ���� ���լҬ���լܬ�
00 // ��Ѭ٬ެ֬� ���լҬ���լܬ�
00 // ��Ѭ٬ެ֬� ��ܬ��
00 // ���ݬ�ڬ߬� ��֬�
00 // ��Ѭ٬ެ֬� �ԬݬѬ�
00 // ��Ѭ٬ެ֬� �٬�Ѭ�ܬ��
00 // �Ԭݬ�Ҭڬ߬� �ԬݬѬ�
00 // ��Ѭ�����߬ڬ� �ԬݬѬ�
00 // �Ӭ����� �ԬݬѬ�
00 // ��٬ܬ���� �ԬݬѬ�
00 // ���ج֬߬ڬ� �� �߬��� (���� �ԬݬѬ٬�)
00 // ���ج֬߬ڬ� �� ���Ѭ� )))
00 // �Ӭ����� �Ҭ��Ӭ֬�
00
00
00
00
00
00
00
00
00
00
00
00
00
00
00
00
00
00
00
00
00
00
00
00
00
00
00
00
00
00
00
00000043
70bb19c1
b8b93fc1
00008a3b

*/