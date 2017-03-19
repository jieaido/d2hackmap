#include "stdafx.h"

#ifdef MODULE_SHOWORBS


void  PermShowOrbPatch() {
	int iLife = D2GetUnitStat(PLAYER , STAT_HP, 0)>>8;
	int iMaxLife=D2GetUnitStat(PLAYER , STAT_MAXHP, 0)>>8;
	if(iMaxLife==0)return;
	if (iLife>iMaxLife)iLife=iMaxLife;
	int iPercent =  100*iLife/iMaxLife ;
	wchar_t wszTemp[64];
	wsprintfW(wszTemp	,	L"%d/%d (%d%%)" , iLife,	iMaxLife,	iPercent);
	
	D2DrawText(wszTemp, 75-(GetTextWidth(wszTemp)>>1), SCREENSIZE.y-95, 0, 0);

	int iMana = D2GetUnitStat(PLAYER , STAT_MANA, 0)>>8;
	int iMaxMana=D2GetUnitStat(PLAYER , STAT_MAXMANA, 0)>>8; 
	if (iMaxMana==0) return;
	if (iMana>iMaxMana)iMana=iMaxMana;
	iPercent = 100*iMana/iMaxMana ;
	wsprintfW(wszTemp	,	L"%d/%d (%d%%)" , iMana,	iMaxMana,	iPercent);

	DrawDefaultFontText(wszTemp,	SCREENSIZE.x-65 ,	SCREENSIZE.y-95,	0);

}

void __declspec(naked) PermShowLifePatch_ASM()
{
	__asm {
		mov  cl , [tPermShowOrb.isOn]
		cmp cl, 0
		je orgcode
		cmp [tPermShowOrb.value], 1
		je orgshow
		call PermShowOrbPatch
		add dword ptr [esp], 0xE3
		ret
orgshow:
		add dword ptr [esp], 0x25
		ret
orgcode:
		mov eax ,[p_D2ScreenSizeY]
		mov eax , [eax]
		cmp ebx, 0x1E
		ret 
		
	}
}


void __declspec(naked) PermShowManaPatch_ASM()
{
	__asm {
		mov  cl , [tPermShowOrb.isOn]
		cmp cl, 0
		je orgcode
		add dword ptr [esp], 0x2D
		ret
orgcode:
		mov ecx ,[p_D2ScreenSizeX]
		mov ecx , [ecx]
		ret 
	}
}


void __declspec(naked) PermShowOrbPatch_ASM()
{
	__asm {
		mov  cl , [tPermShowOrb.isOn]
		cmp cl, 0
		je orgcode
		cmp [tPermShowOrb.value], 1
		jne orgcode
		and word ptr [esp+0x18], 0
		ret
orgcode:
		pop edi			//∑µªÿµÿ÷∑
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 0x25C
		ret
	}
}



#endif