#include "stdafx.h"

#ifdef MODULE_OUTTOWNSELECT

int __fastcall OutTownSelectPatch(UnitAny *pUnit) {
	if ( tOutTownSelect.isOn==0 && fPlayerInTown==FALSE )return -1;
	if (CheckUnitSelect(pUnit)) return 1;
	return -1;
}

void __declspec(naked) OutTownSelectPatch_ASM1() {
	__asm {
		shr eax, 0x15
		and eax, 1
		jnz donothing
		mov ecx, ebp
		call OutTownSelectPatch;
		cmp al, 0xFF
		jz quitcode
		add dword ptr [esp], 0xA2 // adjust return address
		mov [esp+4+0x34], eax // save return result
		pop eax // return address to eax
		push esi // push esi and edi because the return address skips these two instructions
		push edi
		jmp eax
donothing:
		ret
quitcode:
		xor eax, eax
		ret
	}
}

//技能点击玩家会跑过去，这里修正

BOOL __stdcall CheckOutTownSelected( UnitAny *pUnit )
{
	if ( tOutTownSelect.isOn ==0 ) return FALSE;
	if ( fPlayerInTown ) return FALSE;
	if ( pUnit ){
		if ( pUnit->dwUnitType == UNITNO_PLAYER ) return TRUE;
		if ( pUnit->dwUnitType==UNITNO_MONSTER && D2GetMonsterOwner(pUnit->dwUnitId)!= (DWORD)-1 ) return TRUE;
	}
	return FALSE;
}

void __declspec(naked) OutTownSelectPatch_ASM2()
{
	__asm {
// ebx pUnit
		jnz orgcontinue
//check
		push esi
		push edi

		push ebx
		call CheckOutTownSelected;	
		test eax, eax

		pop edi
		pop esi
		jnz orgcontinue
		add dword ptr [esp], 0xA2
orgcontinue:
		ret
	}
}



#endif