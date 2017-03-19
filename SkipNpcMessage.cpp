#include "stdafx.h"

#ifdef MODULE_SKIPNPCMESSAGE


static BOOL fSkipMessageReq = 0 ;
static DWORD mSkipMessageTimer = 0 ;

void  __declspec(naked) NPCMessageLoopPatch_ASM()
{
	__asm {
		test eax , eax
		jne noje
		mov eax ,[mSkipQuestMessage]
		cmp eax , 0				    //未开启功能，不处理
		je oldje
		cmp [fSkipMessageReq] , 0   //非任务信息，不处理
		je oldje
		add [mSkipMessageTimer],1
		cmp [mSkipMessageTimer],eax //小于计时，不处理
		jle oldje
		mov [mSkipMessageTimer],0
		mov eax ,1
		ret
oldje:
		xor eax ,eax
		add dword ptr [esp], 0xB9  // 0F84B8000000
noje:
		ret
	}
}


//任务信息开始
void __declspec(naked) NPCQuestMessageStartPatch_ASM()
{
	__asm {
		mov [fSkipMessageReq],1
		mov [mSkipMessageTimer],0
//oldcode:
		mov ecx, dword ptr [esi+0x0C]
		movzx edx, di
		ret
	}
}

//NPC菜单出现，表示信息结束了
void __declspec(naked) NPCQuestMessageEndPatch1_ASM()
{
	__asm {
		mov [fSkipMessageReq],0
//oldcode:
		mov eax, dword ptr [esp+0x24]
		mov ecx, dword ptr [esp+0x20]
		ret
	}
}

//NPC交互结束，表示信息结束了
void __declspec(naked) NPCQuestMessageEndPatch2_ASM()
{
	__asm {
		mov [fSkipMessageReq],0
//oldcode:
		mov edx, 1
		ret
	}
}






#endif