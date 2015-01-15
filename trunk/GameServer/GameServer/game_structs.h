////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////
#ifndef _GAME_STRUCTS_H_
#define _GAME_STRUCTS_H_

enum ACTION_CHARACTER {
	ACTION_NONE,
	ACTION_MOVE,
	ACTION_JUMP,
	ACTION_FLY
};
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

enum OBJ_MOVE {
	OBJMOVE_NOT_MOVE,
	OBJMOVE_RANDOM,
	OBJMOVE_POINTS
};

enum OBJ_ACTION_STATUS {
	OBJ_ACTION_STAND =2,
	OBJ_ACTION_MOVE = 5
};

typedef struct MOB
{
	unsigned __int32 uid;
	unsigned __int32 zone;
	float base_pos_x;
	float base_pos_y;
	float base_pos_z;
	float base_rotate;
	float pos_x;
	float pos_y;
	float pos_z;
	float next_pos_x;
	float next_pos_y;
	float next_pos_z;
	float rotate;
	unsigned __int32 animation;
	unsigned __int32 resp_time;
	unsigned __int32 type1;
	unsigned __int32 type2;
	unsigned __int32 lvl;
	unsigned __int32 unk1;
	unsigned __int32 unk2;
	unsigned __int32 unk3;
	unsigned __int32 unk4;
	unsigned __int32 unk5;
	unsigned __int32 unk6;
	unsigned __int32 unk7;
	unsigned __int32 unk8;
	unsigned __int32 spawn_id;
	unsigned __int32 unk10;
	unsigned __int32 unk11;
	unsigned __int32 unk12;
	unsigned __int32 unk13;
	unsigned __int32 unk14;
	unsigned __int32 unk15;
	unsigned __int32 unk16;
	unsigned __int32 unk17;
	unsigned __int32 unk18;
	unsigned __int32 unk19;
	unsigned __int32 unk20;
	unsigned __int32 unk21;
	unsigned __int32 unk22;
	int	move;
	int move_distance;
	int action_status;
	bool accounts_show[6000];
} MOB;

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

typedef struct INVENTORY
{
	uint32			PlayerItemUID;
	uint32			item_id;
	int16			count;
	int8			equip;
	int16			sid;
	int16			slot;
} INVENTORY;

typedef struct CHARACTER
{
	uint32			account_id;
	uint32			target_id;
	uint32			id;
	WCHAR			charname[11];
	char			tcharname[21];
	int8			cls;
	int8			sex;
	int8			lvl;
	CHAR_STYLE		style;
	float			pos_x;
	float			pos_y;
	float			pos_z;
	float			rotate;

	float			next_x;
	float			next_y;
	float			next_z;
	float			next_rotate;

	int				action;
	INVENTORY		inventory[_MAX_ITEMS_IN_INVENTORY];
	int				items_in_inventory;
	ACCESS_CHARACTER access;
	int				status;
	bool			ingame;

} CHARACTER;




#endif