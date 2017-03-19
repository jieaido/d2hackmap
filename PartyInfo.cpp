#include "stdafx.h"

#ifdef MODULE_PARTYINFO

void __fastcall DrawPetHeadPath(int xpos , UnitAny *pUnit){
	
	if ( tShowPartyLevel.isOn ){
		wchar_t wszTemp[512];
		wsprintfW( wszTemp, L"%d" ,  D2GetUnitStat(pUnit, STAT_LEVEL, 0) );
		DrawD2Text(1, wszTemp ,	xpos+5 ,	57 ,	0 );
	}

}

void __declspec(naked) DrawPetHeadPath_ASM()
{
	//ecx  xpos
	//eax  ypos
	//ebx  pPet
	__asm {
		push esi

		mov edx , ebx 
		call DrawPetHeadPath

		pop esi
//org
		mov [esp+0x56], 0
		ret
	}
}


void __fastcall DrawPartyHeadPath(int xpos , RosterUnit *pRosterUnit){

	wchar_t wszTemp[512];
	
	if ( tShowPartyLevel.isOn ){
		wsprintfW( wszTemp, L"%d" , pRosterUnit->wLevel );
		DrawD2Text(1, wszTemp ,	xpos+5 ,	57 ,	0 );
	}
	
	if ( tShowPartyPosition.isOn ){
		wsprintfW( wszTemp, L"%d" , pRosterUnit->dwLevelNo );
		DrawCenterText(1, wszTemp ,	xpos+20 ,	15 ,	4 ,1,1);
	}
}

void __declspec(naked) DrawPartyHeadPath_ASM()
{
	//[ebx]  xpos
	//eax  ypos
	//[esp+0C]  pRosterUnit
	__asm {
		mov ecx, dword ptr [ebx]
		mov edx, dword ptr [esp+0xC]

		push ebx
		push edi
		push eax
		
		call DrawPartyHeadPath
		
		pop eax
		pop edi
		pop ebx

		mov ecx, dword ptr [ebx]
		mov edx, dword ptr [esp+0xC]
		ret
	}
}






#endif