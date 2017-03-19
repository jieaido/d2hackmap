#include "stdafx.h"

#ifdef MODULE_PERMSHOWITEM


BOOL PermShowItemsPatch1()
{
	//ALT 按键是否生效
	if ( tLockAltToggle.isOn || tPermShowItems.isOn || D2CheckUiStatus(UIVAR_SHOWITEMS)) return true ;
	return false;
}

BOOL PermShowItemsPatch2() {
	//是否显示人名，false不显示 true 显示
	if( tLockAltToggle.isOn ) return false;

	if ( D2CheckUiStatus(UIVAR_SHOWITEMS) ){
		if ( tPermShowItems.isOn && tPermShowItems.value==3)return true;
		return false;
	}else{
		return tPermShowItems.isOn?true:false;
	}

}

BOOL PermShowItemsPatch3() {
	//是否显示物品名 true 显示  false 不显示
	if( tLockAltToggle.isOn ) return true;

	if ( D2CheckUiStatus(UIVAR_SHOWITEMS) ){
		if ( tPermShowItems.isOn==FALSE) return true ;
		return tPermShowItems.isOn && tPermShowItems.value==1 ;
	}else{
		return tPermShowItems.isOn?true:false;
	}

}

void __declspec(naked) PermShowItemsPatch1_ASM()
{
	__asm {
		call PermShowItemsPatch1
		test eax,eax
		ret
	}
}

void __declspec(naked) PermShowItemsPatch2_ASM()
{
	__asm {
		call PermShowItemsPatch2
		test eax,eax
		je orgcode
		ret
orgcode:
		mov eax, dword ptr [esp+0x20]
		test eax,eax
		ret
	}
}


void __declspec(naked) PermShowItemsPatch3_ASM()
{
	__asm {
		push ebp
		push esi
		call PermShowItemsPatch3
		test eax,eax
		pop esi
		pop ebp
		jz 	outcode
		cmp ebp, 0x20
		jge outcode
		ret
outcode:
		add dword ptr [esp], 0x38A  //to 6FB0DD89
		ret
	}
}

void __declspec(naked) PermShowItemsPatch4_ASM()
{
	__asm {
		push eax
		call PermShowItemsPatch1
		mov ecx, eax
		pop eax
		ret
	}
}



#endif