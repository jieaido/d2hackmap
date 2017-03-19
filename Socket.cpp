#include "stdafx.h"

#ifdef MODULE_SOCKET

void __declspec(naked) FixSocketTimeOut_ASM()
{
		__asm {
		mov eax , [dwSocketTimeOut]
		mov [esp+0x30] ,eax
		ret;
	}
}

void __declspec(naked) FixSocketErrRet_ASM()
{
		__asm {
		mov ebx , eax
		cmp eax, esi
		jle oldje
		mov ecx,[p_D2UnkNetFlag]
		mov ecx,[ecx]
		ret
oldje:
		add dword ptr [esp], 0x14
		ret;
	}
}




#endif