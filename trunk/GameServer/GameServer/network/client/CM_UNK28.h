////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _CM_UNK28_H_
#define _CM_UNK28_H_

void CM_UNK28(PACKET* pck)
{
	int16 unk1 = pck->readW();
	int8 unk2 = pck->readB();
	SM_UNK23(pck);
	SM_UNK25(pck);
	SM_UNK26(pck);
	SM_UNK27(pck);
	SM_UNK28(pck);
	SM_UNK29(pck);
	SM_UNK30(pck);
	SM_UNK31(pck);
	SM_UNK32(pck);
	SM_UNK33(pck);
	SM_UNK34(pck);
	SM_UNK40(pck);
	SM_UNK35(pck);
	SM_UNK36(pck);
	SM_MESSAGE(pck);
	SM_UNK38(pck);
	SM_UNK39(pck);
	SM_UNK_0227(pck);
	SM_UNK_610e(pck);
	SM_UNK_380e(pck);
}

/*

*/

#endif