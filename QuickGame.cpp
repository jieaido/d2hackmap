#include "stdafx.h"

#ifdef MODULE_QUICKGAME

void SaveGameName() {
	if(GAMEINFO->szGameName[0]) {
		wcscpy2(wszGameName, GAMEINFO->szGameName);
		wcscpy2(wszGamePassword, GAMEINFO->szGamePassword);
	}
}

void QuickExitGame(){
	if (fCanExitGame==FALSE)return;
	fCanExitGame = FALSE;
	ExitGame();
}

void QuickNextGame(int addnum)
{
	if (fCanExitGame==FALSE)return;
	fCanExitGame = FALSE;
	wchar_t *nptr = wszGameName+wcslen(wszGameName)-1;
	wchar_t *endptr = nptr+1;
	while (nptr >= wszGameName && (*nptr == L'0' || iswdigit(*nptr))) {
		--nptr;
	}
	if (nptr < endptr-1) {
		long n = wcstol(++nptr, &endptr, 10);
		wchar_t temp[32];
		wsprintfW(temp, L"%d", n+addnum);
		wchar_t *nptr2 = endptr-wcslen(temp);
		if (nptr < nptr2) nptr = nptr2;
		wcscpy(nptr, temp);
	}
	ExitGame();
}


void __fastcall NextGameNamePatch(D2EditBox* box, BOOL (__stdcall *FunCallBack)(D2EditBox*,DWORD,char*))
{
	if (!fAutoNextGameName) return;
	D2SetEditBoxText(box, wszGameName);
	D2SelectEditBoxText(box);
	// original code
	D2SetEditBoxProc(box, FunCallBack);
}
void __fastcall NextGamePasswordPatch(D2EditBox* box, BOOL (__stdcall *FunCallBack)(D2EditBox*,DWORD,char*))
{
	if (!fAutoNextGamePassword) return;
	D2SetEditBoxText(box, wszGamePassword);
	D2SelectEditBoxText(box);
	// original code
	D2SetEditBoxProc(box, FunCallBack);
}


#endif