////////////////////////////////////////////////
// Authors: Tahoma
////////////////////////////////////////////////

#ifndef _SM_PIN_H_
#define _SM_PIN_H_

void SM_PIN(PACKET* pck, int character_id, bool succesful)
{
	++account->pin_erros;
	pck->sql->UpdatePinCode(account->account_id, account->pin_erros);
	pck->CreateBufForSend();
	pck->writeD(0x52);
	pck->writeB(1);
	pck->writeB(2);
	pck->writeW(0);
	pck->writeW(14);
	pck->writeB(5);
	pck->writeB(3);
	pck->writeW(0);
	pck->writeB(1);
	pck->writeB(0);
	pck->writeD(character_id);
	pck->PackSend(OPCODE_SM_PIN);
}

/*
// pin ���ڬ߬��
0e00050500000000000001020000

// ���ڬҬܬ� ���� �ӬӬ�լ� pin
0e00
0505
0000
52000000
01
02
0000
0e00
05
03
0000
01
02
01
00
083b2600
*/
#endif


