
#include "stdafx.h"

#ifdef MODULE_GAMEMONITOR

void DrawMonitorInfo(){
	
	if ( tStateMonitorToggle.isOn==0 ) return ;
	wchar_t wszTemp[512];
	memset(wszTemp , 0 , sizeof(wszTemp));

	int xpos = SCREENSIZE.x-10;
	int ypos = SCREENSIZE.y-130;
	
	DWORD dwTimer = GetTickCount() ;
	DWORD dwOldFone = D2SetTextFont(1);
	for ( int i = 0 ; i < 200 ; i ++ ){	
		
		if ( (int)(sMonitorStr[i].dwStatNo)<=0 )break;
		
		if ( sMonitorStr[i].fEnable ){

			DWORD secs = (dwTimer - sMonitorStr[i].dwTimer)/1000;
			wsprintfW(wszTemp, L"%s: %.2d:%.2d:%.2d",  sMonitorStr[i].wszDesc[dwGameLng],secs/3600, (secs/60)%60, secs%60);
			D2DrawText(wszTemp, xpos-GetTextWidth(wszTemp) , ypos, sMonitorStr[i].dwColor, 0);
			ypos = ypos -15;

		}

	}
	D2SetTextFont(dwOldFone);

}

void ResetMonitor(){
	
	for ( int i = 0 ; i < 200 ; i ++ ){	

		if ( (int)(sMonitorStr[i].dwStatNo)<=0 )break;
		sMonitorStr[i].fEnable = 0 ;

	}

}

void __stdcall SetState( DWORD dwStateNo , BOOL fSet ){
	
	if ( tStateMonitorToggle.isOn==0 ) return ;
	for ( int i = 0 ; i < 200 ; i ++ ){	
		if ( (int)(sMonitorStr[i].dwStatNo)<=0 )break;
		//printMsg(" szName= %s" ,PLAYER->pPlayerData->szName);
		//printMsg(" pObjectTxt= %s" ,PLAYER->pObjectData->pObjectTxt);
		if ( (int)dwStateNo == 55 && PLAYER->pSkill->pRightSkill->pSkillInfo->wSkillId == 151){
			//TODO 这里禁止攻击
			//fPlayerInTown = 1;
			//printMsg(" stop attck ");
			HWND	hwnd = D2GetHwnd(); 
			POINT p;
			//先计算出鼠标相对位置
			GetCursorPos(&p);
			//SendMessage(hwnd, WM_RBUTTONUP, NULL, NULL);
			SendMessage(hwnd, WM_RBUTTONUP, NULL, MAKELONG(400, 300));
			SendMessage(hwnd, WM_LBUTTONDOWN, NULL, MAKELONG(400, 300));
			SendMessage(hwnd, WM_LBUTTONUP, NULL, MAKELONG(400, 300));
		}
		if ( sMonitorStr[i].dwStatNo==dwStateNo ){
			sMonitorStr[i].fEnable = fSet;
			sMonitorStr[i].dwTimer = GetTickCount() ;
			break;
		}
	}

}

void __declspec(naked) RecvCommand_A7_Patch_ASM()
{
	__asm{

		mov esi, ecx
		movzx edx, byte ptr [esi+1]
		mov ecx, dword ptr [esi+2]

		cmp edx , 0
		jne  org
		cmp ecx ,[dwPlayerId]
		jne org
		movzx eax, byte ptr [esi+06]
		
		push ecx
		push edx
		push esi 

		push 1
		push eax
		call SetState

		pop esi
		pop edx
		pop ecx
org:
		ret


	}

}

void __declspec(naked) RecvCommand_A8_Patch_ASM()
{
	__asm{

		mov esi, ecx
		movzx edx, byte ptr [esi+1]
		mov ecx, dword ptr [esi+2]

		cmp edx , 0
		jne  org
		cmp ecx ,[dwPlayerId]
		jne org
		movzx eax, byte ptr [esi+07]
		
		push ecx
		push edx
		push esi 

		push 1
		push eax
		call SetState

		pop esi
		pop edx
		pop ecx
org:
		ret

	}

}



void __declspec(naked) RecvCommand_A9_Patch_ASM()
{
	__asm{

		mov esi, ecx
		movzx edx, byte ptr [esi+1]
		mov ecx, dword ptr [esi+2]

		cmp edx , 0
		jne  org
		cmp ecx ,[dwPlayerId]
		jne org
		movzx eax, byte ptr [esi+06]
		
		push ecx
		push edx
		push esi 

		push 0
		push eax
		call SetState

		pop esi
		pop edx
		pop ecx
org:
		ret

	}

}
#endif