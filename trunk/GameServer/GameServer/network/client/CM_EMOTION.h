////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_EMOTION_H_
#define _CM_EMOTION_H_

inline void CM_EMOTION(PACKET* pck)
{
	int8 unk2 = pck->readB();
	SM_UNK_2810(pck);
}

/*
1800 0173
00200000
00E86208               ...s. ....b.
*/

#endif