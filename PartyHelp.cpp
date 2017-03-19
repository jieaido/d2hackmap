#include "stdafx.h"

#ifdef MODULE_PARTYHELP

static MyTimer stTimer[8];

void ResponseInvite(){
	if (tAutoParty.isOn){
		for (int i=0; i<8 ; i++ ){
			if ( stTimer[i].fEnable == TRUE ){
				if ( GetTickCount()-stTimer[i].dwTimer>mAutoPartyDelays){

					BYTE acceptInvite[6] = {0x5E,0x08};
					*(DWORD*)&acceptInvite[2] =stTimer[i].dwValue;
					D2SendPacket(sizeof(acceptInvite), 0, acceptInvite);

					memset( stTimer ,  0 , sizeof(stTimer));
					return;
				}
			}
		}
	}
}

BOOL CheckInvite() {
	if ( dwPlayerId==1 )return TRUE;

	for (RosterUnit *pUnit = PLAYERLIST; pUnit; pUnit = pUnit->pNext)
	{
		if (pUnit->dwUnitId<dwPlayerId) return FALSE; //自己不是最小编号，放弃邀请权利
	}
	return TRUE;
}

void InviteAll() {
	for (RosterUnit *pUnit = PLAYERLIST; pUnit; pUnit = pUnit->pNext)
	{
		if (pUnit->dwUnitId==dwPlayerId || pUnit->dwPartyFlags)
			continue;
		BYTE InvitePlayer[6] = {0x5E,0x06};
		*(DWORD*)&InvitePlayer[2] = pUnit->dwUnitId;
		D2SendPacket(sizeof(InvitePlayer), 0, InvitePlayer);
	}
}

void PermitAll() {

	for (RosterUnit *pUnit = PLAYERLIST; pUnit; pUnit = pUnit->pNext)
	{
		if (pUnit->dwUnitId==dwPlayerId )
			continue;

		BYTE PermitPlayer[7] = {0x5D,0x01,0x01};
		*(DWORD*)&PermitPlayer[3] = pUnit->dwUnitId;
		D2SendPacket(sizeof(PermitPlayer), 0, PermitPlayer);
	}
	
}

void __stdcall AutoParty(BYTE *aPacket)
{
	if ( tAutoParty.isOn && aPacket[1] == 0x07 && aPacket[2] == 0x02 && aPacket[7] == 0x05 )
	{
		// Player Is Asking To Party With You
		// Player ID = aPacket[3~6]
		// Send packet back: 5E 08 xx xx xx xx
		for (int i=0; i<8 ; i++ ){
			if ( stTimer[i].fEnable == FALSE ){
				stTimer[i].dwValue = *(DWORD*)&aPacket[3];
				stTimer[i].dwTimer =  GetTickCount();
				stTimer[i].fEnable = TRUE;
				break;
			}
		}

	}
	else if(aPacket[1] == 0x03 || aPacket[1] == 0x00)
	{
		if( CheckInvite() ) fCanInvite = TRUE; //有玩家离开游戏
	}
}
void __declspec(naked) RecvCommand_5A_Patch_ASM()
{
	__asm
	{
		pop eax  //ret code

		sub esp, 0x28
		push esi
		push edi

		push eax //ret code

		push ecx

		push ecx;
		call AutoParty;

		pop ecx
		
		ret
	}
}


void __stdcall AutoInvite(BYTE *aPacket)
{
	if (tAutoInvite.isOn && fCanInvite )
	{
		//自动邀请
		DWORD recPlayerId= *(DWORD*)&aPacket[3];
		if (recPlayerId==dwPlayerId) return;
		BYTE InvitePlayer[6] = {0x5E,0x06};
		InvitePlayer[2] = aPacket[3];
		InvitePlayer[3] = aPacket[4];
		InvitePlayer[4] = aPacket[5];
		InvitePlayer[5] = aPacket[6];
		D2SendPacket(sizeof(InvitePlayer), 0, InvitePlayer);		
	}

	if ( tAutoPermit.isOn && fCanPermit ){
		//自动开锁
		DWORD recPlayerId= *(DWORD*)&aPacket[3];
		if (recPlayerId==dwPlayerId) return;
		BYTE PermitPlayer[7] = {0x5D,0x01,0x01};
		PermitPlayer[3] = aPacket[3];
		PermitPlayer[4] = aPacket[4];
		PermitPlayer[5] = aPacket[5];
		PermitPlayer[6] = aPacket[6];
		D2SendPacket(sizeof(PermitPlayer), 0, PermitPlayer);

	}

}

void __declspec(naked) RecvCommand_5B_Patch_ASM()
{
	__asm
	{
		//ecx = cmdbuf
		pop eax

		push esi

		push eax //ret code
		
		push ecx

		push ecx
		call AutoInvite

		pop ecx

		lea esi, dword ptr [ecx+22]
		mov eax, esi
		ret
	}
}






#endif