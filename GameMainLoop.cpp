#include "stdafx.h"
HINSTANCE hinst; 


struct thread_data
{
 int m_id;
 thread_data(int id) : m_id(id) {}
};

DWORD WINAPI thread_func(LPVOID lpParameter)
{
 thread_data *td = (thread_data*)lpParameter;
 HWND hwnd = D2GetHwnd();
 D2WinMain();
 return 0;
}

void GameLoopPatch()
{
	static wchar_t *wszProgTitle = L"<Hackmap>: Payallmoney's Map 1.0 ,  base on virgol (4.6) installed.";	
	if ( fInGame==FALSE ) {
		fInGame = TRUE;

		D2ShowGameMessage( wszProgTitle, 0);
		ShowWarningMessage();
		
		if(fEnterGameSound){
			MessageBeep(MB_ICONEXCLAMATION);
		}

		#define RUN_ONCE
			#include "Module.h"
		#undef RUN_ONCE

		if ( wszCFGVersion[dwGameLng][0] ) {
			//D2ShowGameMessage( wszCFGVersion[dwGameLng], 9);
		}
		HWND hwnd = D2GetHwnd();
		//新建窗口用来传递消息
		CreateThread(NULL, 0, thread_func, new thread_data(1) , 0, 0);	
		SetWindowText(D2EventHwnd,TEXT(D2EVENTWIN_TITLE));
	}
	dwCurrentAct = PLAYER->dwAct;
	dwCurrentLevel = PLAYER->pMonPath->pRoom1->pRoom2->pDrlgLevel->dwLevelNo;
	fPlayerInTown = (LEVELNO==actlvls[ACTNO]);
	#define RUN_LOOP
		#include "Module.h"
	#undef RUN_LOOP

}

void GameEndPatch()
{
	if ( fInGame ){
	
		fInGame = FALSE;
		fPlayerInTown = TRUE;
		#define RUN_ENDGAME
			#include "Module.h"
		#undef RUN_ENDGAME

	}
}

void __declspec(naked) GameLoopPatch_ASM()
{
	__asm {
		pop eax
		sub esp, 0x20
		mov [esp+0x0c], ecx
		push eax
		jmp GameLoopPatch
	}
}

void __declspec(naked) GameEndPatch_ASM()
{
	__asm {
		call GameEndPatch
		mov ecx,0xb4
		ret
	}
}
