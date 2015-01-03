////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_EXIT_H_
#define _CM_EXIT_H_

inline void CM_EXIT(PACKET* pck)
{
	int16 unk1 = pck->readW();
	uint32 unk2 = pck->readD();
	uint32 unk3 = pck->readD();
	uint32 unk4 = pck->readD();
	uint32 unk5 = pck->readD();
//	pck->Disconnect();
}

/*
01560800
35003700
38003400
68006a00
0a00bfe1
*/

#endif