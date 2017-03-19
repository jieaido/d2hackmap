#include "stdafx.h"


#ifdef MODULE_QUICKBACKTOWN

DWORD CalSrollOfTownportal(){
	if (PLAYER->pSkill){
		Skill *pSkill = PLAYER->pSkill->pFirstSkill;
		
		while(pSkill){
			if(pSkill->pSkillInfo->wSkillId == 220){
				return pSkill->dwQuality;
			}
			pSkill= pSkill->pNextSkill;
		}
	}
	return 0;
}

void BackToTown()
{
	UnitAny *pUnit = PLAYER;
	if( fPlayerInTown ) return;
	fBackToTown = TRUE;

	BYTE castTP1[9] = {0x3C};
	*(DWORD*)&castTP1[1] = 0xDC;
	*(DWORD*)&castTP1[5] = 0xFFFFFFFF;
	D2SendPacket(sizeof(castTP1), 0, castTP1);
	
	BYTE castTP2[5] = {0x0C};
	*(WORD*)&castTP2[1] = pUnit->pMonPath->wTargetX;
	*(WORD*)&castTP2[3] = pUnit->pMonPath->wTargetY;
	D2SendPacket(sizeof(castTP2), 0, castTP2);

}


void OpenDoor()
{
	UnitAny *pUnit = PLAYER;
	if( fPlayerInTown ) return;
	fBackToTown = FALSE;

	BYTE castTP1[9] = {0x3C};
	*(DWORD*)&castTP1[1] = 0xDC;
	*(DWORD*)&castTP1[5] = 0xFFFFFFFF;
	D2SendPacket(sizeof(castTP1), 0, castTP1);
	
	BYTE castTP2[5] = {0x0C};
	*(WORD*)&castTP2[1] = pUnit->pMonPath->wTargetX;
	*(WORD*)&castTP2[3] = pUnit->pMonPath->wTargetY;
	D2SendPacket(sizeof(castTP2), 0, castTP2);

}

void __fastcall AutoBackToTown(BYTE *aPacket)
{
	if( aPacket[0]==0x60 && aPacket[1] == 0x00 ) //00限定只能走通向城里的传送门
	{
		if ( fBackToTown && tNoBackToTown.isOn == 0 ){
			fBackToTown = FALSE;
			BYTE castMove[9] = {0x13};
			*(DWORD*)&castMove[1] = 2;
			*(DWORD*)&castMove[5] = *(DWORD*)&aPacket[3]; // portal ID
			D2SendPacket(sizeof(castMove), 0, castMove);
		}

		if( nTownportalAlertNums!= (DWORD)-1 ){
			DWORD srollcount = CalSrollOfTownportal();
			if ( srollcount<= nTownportalAlertNums ){
				wchar_t temp[512];
				wsprintfW(temp,  L"<Hackmap>: Warning !! Only %d Townportals Left ", srollcount);
				D2ShowGameMessage(temp, 8);
			}
		}

	}
}





void __declspec(naked) RecvCommand_60_Patch_ASM()
{
	__asm
	{
		//ecx = cmdbuf
		push ecx

		call AutoBackToTown;

		pop ecx

		pop edx //ret code
//org:
		sub esp, 8
		mov eax, dword ptr [ecx]
		jmp edx
	}
}




#endif