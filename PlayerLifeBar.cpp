#include "stdafx.h"

#ifdef MODULE_PLAYERLIFEBAR

int GetPlayerHpPercent(UnitAny *pUnit){
	for( RosterUnit *pRosterUnit = PLAYERLIST ;pRosterUnit ; pRosterUnit=pRosterUnit->pNext ){
		if( pUnit->dwUnitId == pRosterUnit->dwUnitId) return pRosterUnit->dwPartyLife ;
	}
	return 0;
}

void __fastcall PlayerNamePatch(wchar_t *wszName, UnitAny *pUnit){
	

	if (tPlayerLevel.isOn) {
		int lvl = D2GetUnitStat(pUnit, STAT_LEVEL, 0);
		wsprintfW(wszName+wcslen(wszName),  L" (L%d)", lvl);
	}

	if ( tPlayerHPPercent.isOn ){
		wsprintfW(wszName+wcslen(wszName),  L" (%d%%)", GetPlayerHpPercent(pUnit));
	}
	
	if ( tPlayerDistance.isOn ){
		char strVal [10] ;
		DblToStr( GetUnitDistanceInSubtiles(pUnit,PLAYER) ,2 , strVal);
		wsprintfW2(wszName+wcslen(wszName), " (%s yards)", strVal);
	}

}

void __declspec(naked) PlayerNamePatch_ASM()
{
	//ecx  wszName
	//ebp  pUnit
	__asm {
		push ecx
		push edx
		mov edx ,ebp
		call PlayerNamePatch
		pop edx
		pop ecx
		jmp D2DrawUnitLifeBar
	}
}



#endif