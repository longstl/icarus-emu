////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_GETAREA_H_
#define _CM_GETAREA_H_

void CM_GETAREA(PACKET* pck)
{
	int16 unk1 = pck->readW();
	int8 unk2 = pck->readB();
	SM_SETAREA(pck);	
}

/*



*/

#endif