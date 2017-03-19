#include "stdafx.h"

#ifdef MODULE_GAMECOUNT

//放在ScreenHook.cpp里调用
void ShowGameCount(){

	int xpos = SCREENSIZE.x/2 + 70;
	int ypos = SCREENSIZE.y - 50;
	DWORD dwOldFone = D2SetTextFont(1);

	if ( tGetHitCount.isOn ){	
		wchar_t wszTemp[512];
		DWORD dwColor = tGetHitCount.value-1 ;
		wcscpy( wszTemp , L"GetHits:" );
		D2DrawText(wszTemp, xpos,  ypos, dwColor, 0);

		wsprintfW(wszTemp ,L"%d" , dwGetHits );
		D2DrawText(wszTemp, xpos+65,  ypos, dwColor, 0);

		wsprintfW(wszTemp ,L"Total: %d" , dwGetHitSum );
		D2DrawText(wszTemp, xpos+105,  ypos, dwColor , 0);
		ypos = ypos-15;
	}

	if ( tKillCount.isOn ){	
		wchar_t wszTemp[512];
		DWORD dwColor = tKillCount.value-1 ;
		wcscpy( wszTemp , L"Kills:" );
		D2DrawText(wszTemp, xpos+20,  ypos, dwColor, 0);

		wsprintfW(wszTemp ,L"%d" , dwGameKills );
		D2DrawText(wszTemp, xpos+65,  ypos, dwColor, 0);

		wsprintfW(wszTemp ,L"Total: %d" , dwKillSum );
		D2DrawText(wszTemp, xpos+105,  ypos, dwColor, 0);
	}

	D2SetTextFont(dwOldFone);
}

void __fastcall SetKills( DWORD newKills ){

	if ( (int)newKills > (int)dwLastKills ) {
		dwKillSum++;
		dwGameKills++;
	}
	dwLastKills = newKills;

}
void __declspec(naked) KillCountPatch_ASM()
{
	//死亡一次会减少一次杀敌数，所以可能变负数
	//记录下上次值，如果小于上次，认为死亡~
	__asm{

		push esi
		push eax
		
		movsx ecx, si
		call SetKills

		pop eax
		pop esi
		test esi,0x8000
		ret 

	}
}

void __declspec(naked) UnitModeChangePatch_ASM()
{
	__asm{
		cmp edi , 4
		jne org

		mov edx, dword ptr [esi]
		cmp edx, 0
		jne org
		
		cmp [dwOrgMode] ,0
		je gocount
		mov [dwOrgMode] ,0
		jmp org
gocount:
		mov edx , dword ptr [esi+0x10] //单机会连着两次，但战网模式正常,记录下上一次调用的原值，并在全局循环中重置
		mov [dwOrgMode] , edx 
		add [dwGetHits] , 1
		add [dwGetHitSum] , 1
org:
		mov edx, dword ptr [esi+0xC4]
		ret 
	}
}



#endif