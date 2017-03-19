#include "stdafx.h"

#ifdef MODULE_GAMECHAT


BOOL fMyChatOn = FALSE;
void SendChatMessage(char *myMsg)
{
	if( fInGame==FALSE )return;
	if( D2CheckUiStatus(UIVAR_CHATINPUT) ) return;

	fMyChatOn = TRUE;

	D2SetUiStatus( UIVAR_CHATINPUT , 0 , 1);
	wcscpy2( p_D2LastChatMessage, myMsg );
	D2MSG pmsg;
	pmsg.hwnd = D2GetHwnd();
	pmsg.wParam = 13;
	pmsg.xpos = 1;
	pmsg.ypos = 28;
	D2ChatInput(&pmsg);

	fMyChatOn = FALSE;
}

void WisperPatch()
{
	if (tWisperNotice.isOn){
		static char NoticeMsg[] = "Someone wisper me.";
		SendChatMessage(NoticeMsg);
	}
}

void __declspec(naked) WisperPatch_ASM()
{
	__asm {
		pushad
		call WisperPatch;	
		popad
		mov ecx, 0x000014D4
		ret
	}

}

void CheckD2WinEditBox()
{
	if (pD2WinEditBox) {
		if ( D2CheckUiStatus(UIVAR_CHATINPUT) ) {
			if( *(DWORD*)p_D2LastChatMessage != 0xAD5AFFFF) {
				D2DestroyEditBox(pD2WinEditBox);
				pD2WinEditBox = NULL;
				FOCUSECONTROL = NULL;
			}
			D2SetTextFont(1);
		}
	}
}

BOOL __cdecl InputLinePatch(BYTE keycode)
{
	if ( fMyChatOn==FALSE && keycode != VK_ESCAPE) {
		if (keycode != VK_RETURN) return TRUE;
		if (pD2WinEditBox) {
			wcscpy(p_D2LastChatMessage, D2GetEditBoxText(pD2WinEditBox));
		}
	}
	return FALSE;
}

void __declspec(naked) InputLinePatch1_ASM()
{
	__asm {
		mov ebx, eax
		push [edi+8]
		call InputLinePatch
		test eax, eax
		pop eax
		jz quitcode
		add dword ptr [esp], 0x427 // add to the point where function returns
quitcode:
		ret
	}
}

BOOL __stdcall EditBoxCallBack(D2EditBox* pEditBox, DWORD dwLength, char *pChar)
{
	return TRUE;
}


BOOL __cdecl InitD2EditBox()
{	
	if ( fMyChatOn ) return FALSE;
	if(!pD2WinEditBox) {
		static DWORD dws[] = {0x0D, 0};//ËùÓÃ×ÖÌå
		pD2WinEditBox = D2CreateEditBox(0x83,
			SCREENSIZE.y-58, SCREENSIZE.x-266,
			0x2D,
			0, 0, 0, 0, 0,
			sizeof(dws), &dws
			);
		FOCUSECONTROL = pD2WinEditBox;
		if (pD2WinEditBox) {
			D2SetEditBoxProc(pD2WinEditBox, &EditBoxCallBack);
			D2SetEditBoxText(pD2WinEditBox, p_D2LastChatMessage);
		}
		*(DWORD*)p_D2LastChatMessage = 0x0AD5AFFFF;
	}
	if (pD2WinEditBox)
		(pD2WinEditBox->fnCallBack)(pD2WinEditBox);
	return TRUE;
}

void __declspec(naked) InputLinePatch2_ASM()
{
	__asm {
		call InitD2EditBox
		test eax, eax
		jz quitcode
		add dword ptr [esp], 0x154
quitcode:
		mov ecx, p_D2LastChatMessage
		ret
	}
}

BOOL __stdcall SelectTextPatch1(char*sDesc){
	
	if (pD2WinEditBox){
		DWORD dwStart;
		DWORD n;
		DWORD len;
		LPWSTR	lpText;
		lpText = (LPWSTR)(pD2WinEditBox->wszText);
		if (pD2WinEditBox->dwSelectStart == (DWORD)-1) return FALSE;
		if (pD2WinEditBox->dwSelectStart == pD2WinEditBox->dwSelectEnd) return FALSE;
		if (pD2WinEditBox->dwSelectStart > pD2WinEditBox->dwSelectEnd) {
			dwStart = pD2WinEditBox->dwSelectEnd;
			len = pD2WinEditBox->dwSelectStart - dwStart;
		} else {
			dwStart = pD2WinEditBox->dwSelectStart;
			len = pD2WinEditBox->dwSelectEnd - dwStart;
		}
		n = WideCharToMultiByte(CP_ACP, 0, lpText + dwStart, len, sDesc, (len+1)*2, NULL, NULL);
		sDesc[n] = 0;
		return TRUE;
	}
	return FALSE;
}

void __declspec(naked) SelectTextPatch1_ASM()
{
	__asm {
		push ecx
		push edx

		push edx
		call SelectTextPatch1
		test eax , eax

		pop edx
		pop ecx
		jz  org
		ret
org:
		mov byte ptr [esp+esi+0x88], 0
		ret;
	}
}


BOOL __stdcall SelectTextPatch2(char*sDesc){
	
	if (pD2WinEditBox){
		DWORD dwStart;
		DWORD n;
		LPWSTR	lpText;
		lpText = (LPWSTR)(pD2WinEditBox->wszText);
		if (pD2WinEditBox->dwSelectStart == (DWORD)-1) return FALSE;
		if (pD2WinEditBox->dwSelectStart == pD2WinEditBox->dwSelectEnd) return FALSE;
		if (pD2WinEditBox->dwSelectStart > pD2WinEditBox->dwSelectEnd) {
			dwStart = pD2WinEditBox->dwSelectEnd;
		} else {
			dwStart = pD2WinEditBox->dwSelectStart;
		}
		n = WideCharToMultiByte(CP_ACP, 0, lpText, dwStart, sDesc, (dwStart+1)*2, NULL, NULL);
		sDesc[n] = 0;
		return TRUE;
	}
	return FALSE;
}

void __declspec(naked) SelectTextPatch2_ASM()
{
	__asm {
		push ecx
		push edx

		push edx
		call SelectTextPatch2
		test eax , eax

		pop edx
		pop ecx
		jz  org
		ret
org:
		mov byte ptr [esp+ebp+0x88], 0
		ret;
	}
}

#endif