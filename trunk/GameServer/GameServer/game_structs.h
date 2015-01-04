#ifndef _GAME_STRUCTS_H_
#define _GAME_STRUCTS_H_

#pragma pack(1)
typedef struct CHAR_STYLE
{
	uint16			unk0;
	uint32			unk1;
	uint8			eye;			// ¬æ¬à¬â¬Þ¬Ñ ¬Ô¬Ý¬Ñ¬Ù
	uint8			unk2;
	uint8			eyebrows;		// ¬Ò¬â¬à¬Ó¬Ú
	uint8			unk3;
	uint8			iris;			// ¬Ù¬â¬Ñ¬é¬Ö¬Ü
	uint16			unk4;
	uint8			unk5;
	uint8			tatoo;			// ¬ä¬Ñ¬ä¬å
	uint16			unk6;
	uint8			unk7;
	uint16			unk81;
	uint16			unk8;			// 0x0000 
	uint32			unk9;			// 0xffffffff
	uint8			hair;			// ¬á¬â¬Ú¬é¬Ö¬ã¬Ü¬Ñ
	uint16			unk10;
	uint8			unk11; // 24
	uint32			unk12;			// 0xffffffff
	uint32			unk13;
	uint32			unk14;
	uint32			color_lips;		// ¬è¬Ó¬Ö¬ä ¬Ô¬å¬Ò
	uint32			color_eyeb;		// ¬è¬Ó¬Ö¬ä ¬Ò¬Ö¬Ý¬Ü¬Ñ
	uint32			color_iris;		// ¬è¬Ó¬Ö¬ä ¬â¬Ñ¬Õ¬å¬Ø¬Ü¬Ú
	uint32			color_eyebrows;	// ¬è¬Ó¬Ö¬ä ¬Ò¬â¬à¬Ó¬Ö¬Û
	uint32			color_eye;		// ¬Ô¬Ó¬Ö¬ä ¬Ô¬Ý¬Ñ¬Ù
	uint32			unk15;
	uint32			unk16;
	uint32			unk17;
	uint32			unk18;
	uint32			unk19;
	uint32			unk20;
	uint32			unk21;
	uint32			unk22;
	uint32			unk23;
	uint32			unk24;
	uint32			unk25;
	uint32			unk26;
	uint32			unk27;
	uint32			unk28;
	uint32			unk29;
	uint32			unk30;
	uint32			unk31;
	uint32			unk32;
	uint32			unk33;
	uint32			unk34;
	uint32			unk35;
	uint32			unk36;
	uint32			unk37;
} CHAR_STYLE;
#pragma pack()

enum ACCESS_CHARACTER {
	ACCESS_CHARACTER_PLAYER = 0,
	ACCESS_CHARACTER_GAMEMASTER = 1,
	ACCESS_CHARACTER_ADMINISTRATOR = 2
};

enum CHARACTER_STATUS {
	STATUS_NONE,
	STATUS_CONNECT,
	STATUS_SM_UNK3,
	STATUS_GETAREA,
	STATUS_GETINFO
};

typedef struct CHARACTER
{
	uint32			account_id;
	uint32			id;
	WCHAR			charname[10];
	int8			cls;
	int8			sex;
	int8			lvl;
	CHAR_STYLE		style;
	float			pos_x;
	float			pos_y;
	float			pos_z;
	float			rotate;
	ACCESS_CHARACTER access;
	int				status;

} CHARACTER;




#endif