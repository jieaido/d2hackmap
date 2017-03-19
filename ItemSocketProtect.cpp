
#include "stdafx.h"

#ifdef MODULE_ITEMSOCKETPROTECT

void ShowSocketProtectInfo(){
	D2ShowPartyMessage( L"<Hackmap>: Socket Protect On", 8);
}

void __declspec(naked) SocketProtectPatch_ASM()
{
	__asm {
		mov eax, p_D2PlayerUnit
		mov eax, [eax]
		push 0x13
		push eax
		call D2ItemProtect
		call ShowSocketProtectInfo
		ret
	}
}

void __declspec(naked) SocketProtectPatch1_ASM()
{
	__asm {
		cmp [tSocketProtect.isOn], 0
		jz outcode
		call SocketProtectPatch_ASM
		add dword ptr [esp], 0x47 
		ret
outcode:
// original code
		mov eax, [esp+4+0x18] 
		test eax, eax
		ret
	}
}

void __declspec(naked) SocketProtectPatch2_ASM()
{
	__asm {
		cmp [tSocketProtect.isOn], 0
		jz outcode
		call SocketProtectPatch_ASM
		add dword ptr [esp], 0x36
		ret
outcode:
		mov eax, [esp+4+0x44] // 4 bytes for return address
		test eax, eax
		ret
	}
}




#endif