#include "stdafx.h"

#ifdef MODULE_UNICODESUPPORT

#define		KEY_CODE_COPY			0x03
#define		KEY_CODE_PASTE			0x16
#define		KEY_CODE_CUT			0x18
#define		KEY_CODE_ENTER			'\r'

#define EDITBOX_MAX_CHAR_COUNT		196

void UnicodeFix(LPWSTR lpText, DWORD * dwPos)
{
	DWORD len, i, j;
	WORD  char1, char2;
	WORD  uchar;
	BYTE  mbchar[2];
	DWORD	dwOldPos;
	DWORD	dwNewPos;

	if (!lpText) return;
	len = wcslen(lpText);
	if (dwPos) dwOldPos = *dwPos;
	else dwOldPos = 0;
	if (len >= 2) {
		dwNewPos = -1;
		for (i=0, j = 0; i < len; i++) {
			char1 = lpText[i];
			char2 = lpText[i+1];
			if (i == dwOldPos) {
				dwNewPos = j;
			}
			//a non-english character
			if (!HIBYTE(char1) && (char1) & 0x80 && char1 != 0xff && LOBYTE(char2)) {
				mbchar[0] = LOBYTE(char1);
				mbchar[1] = LOBYTE(char2);
				if( fLocalizationSupport==3 ) GB2GBK((char *)mbchar);
				if (MultiByteToWideChar(CP_ACP, 0, (char *)mbchar, sizeof(mbchar), (LPWSTR)&uchar, 1)) {
					//GbToBig5(&uchar);
					lpText[j++] =uchar;
					i++;
					if (i == dwOldPos) {
						dwNewPos = j-1;
					}
				} else {
					lpText[j++] = char1;
				}
			} else {
				lpText[j++] = char1;
			}
		}
		if (dwNewPos == (DWORD)-1) {
			dwNewPos = j;
		}
		lpText[j] = 0;
	} else {
		dwNewPos = dwOldPos;
	}
	if (dwPos) *dwPos = dwNewPos;
	return;
}

LPCSTR __fastcall D2Lang_Unicode2WinPatch(LPSTR lpWinStr, LPWSTR lpUnicodeStr, DWORD dwBufSize)
{
	WideCharToMultiByte(CP_ACP, 0, lpUnicodeStr, -1, lpWinStr, dwBufSize, NULL, NULL);
	return lpWinStr;
}

LPWSTR __fastcall D2Lang_Win2UnicodePatch(LPWSTR lpUnicodeStr, LPCSTR lpWinStr, DWORD dwBufSize)
{
	MyMultiByteToWideChar(CP_ACP, 0, lpWinStr, -1, lpUnicodeStr, dwBufSize);
	return lpUnicodeStr;
}


void EditDeleteSelect(D2EditBox *hWnd)
{
	DWORD dwStart;
	DWORD len, i, j;

	if (hWnd->dwSelectStart == (DWORD)-1) return;
	if (hWnd->dwSelectStart == hWnd->dwSelectEnd) return;
	if (hWnd->dwSelectStart > hWnd->dwSelectEnd) {
		dwStart = hWnd->dwSelectEnd;
		len = hWnd->dwSelectStart - dwStart;
	} else {
		dwStart = hWnd->dwSelectStart;
		len = hWnd->dwSelectEnd - dwStart;
	}
	hWnd->dwSelectStart = (DWORD)-1;
	hWnd->dwSelectEnd = 0;
	i = dwStart;
	j = dwStart + len;
	while (1) {
		if (!hWnd->wszText[j]) break;
		hWnd->wszText[i++] = hWnd->wszText[j++];
	}
	hWnd->wszText[i] = 0;
	if (hWnd->dwCursorPos > dwStart && hWnd->dwCursorPos < dwStart + len) {
		hWnd->dwCursorPos = dwStart;
	} else if (hWnd->dwCursorPos >= dwStart+len) {
		hWnd->dwCursorPos -= len;
	}
	return;
}


DWORD __fastcall ChannelEnterCharPatch(D2EditBox *hWnd, BYTE bKeyCode)
{
	DWORD	ret;
	LPWSTR	lpText;
	DWORD len;
	WORD  char1;
	WORD  uchar;
	BYTE	mbchar[2];
	DWORD	dwPos;
	HGLOBAL hGlobal;
	LPSTR  lpStr;
	static BYTE lastcode = 0;
	
	lpText = (LPWSTR)(hWnd->wszText);
	len = wcslen(lpText);
	if (!len) memset( hWnd->wszText, 0, sizeof(hWnd->wszText) );
	if (hWnd->dwCursorPos > len) hWnd->dwCursorPos = len;
	if (hWnd->dwCursorPos > 0) {
		char1 = lastcode;
		if (!HIBYTE(char1) && (char1) & 0x80 && char1 != 0xff) {
			mbchar[0] = LOBYTE(char1);
			mbchar[1] = bKeyCode;
			lastcode = 0;
			if( fLocalizationSupport==3 ) GB2GBK((char *)mbchar);
			if (MultiByteToWideChar(CP_ACP, 0, (char *)mbchar, sizeof(mbchar), (LPWSTR)&uchar, 1)) {
				lpText[hWnd->dwCursorPos-1] = uchar;
				return TRUE;
			}
		}
		
	}
	if (bKeyCode == KEY_CODE_PASTE) {
		ret = D2AddEditBoxChar(hWnd, bKeyCode);
		dwPos = hWnd->dwCursorPos;
		UnicodeFix(lpText, &dwPos);
		hWnd->dwCursorPos = dwPos;
		return ret;
	} else if (bKeyCode == KEY_CODE_COPY || bKeyCode == KEY_CODE_CUT) {
		DWORD dwStart;
		DWORD n;

		if (hWnd->dwSelectStart == (DWORD)-1) return FALSE;
		if (hWnd->dwSelectStart == hWnd->dwSelectEnd) return FALSE;
		if (hWnd->dwSelectStart > hWnd->dwSelectEnd) {
			dwStart = hWnd->dwSelectEnd;
			len = hWnd->dwSelectStart - dwStart;
		} else {
			dwStart = hWnd->dwSelectStart;
			len = hWnd->dwSelectEnd - dwStart;
		}
		if (!OpenClipboard(NULL)) return FALSE;
		EmptyClipboard();
		hGlobal = GlobalAlloc(GMEM_MOVEABLE, (len+1) * 2); 
		if (hGlobal && (lpStr = (LPSTR)GlobalLock(hGlobal))) {
			n = WideCharToMultiByte(CP_ACP, 0, lpText + dwStart, len, lpStr, (len+1)*2, NULL, NULL);
			lpStr[n] = 0;
			GlobalUnlock(hGlobal);
			SetClipboardData(CF_TEXT, hGlobal);
		}
		CloseClipboard();
		if (hGlobal) GlobalFree(hGlobal);
		if (bKeyCode == KEY_CODE_CUT) EditDeleteSelect(hWnd);
		return TRUE;
	}
	if (bKeyCode >= ' ') {

		if ((bKeyCode & 0x80) && (bKeyCode != 0xff)) {
			lastcode = bKeyCode;
			ret = D2AddEditBoxChar(hWnd, 33);
		}else{
			ret = D2AddEditBoxChar(hWnd, bKeyCode);
		}
		UnicodeFix(hWnd->wszText, &hWnd->dwCursorPos);

		return ret;
	}
	ret = D2AddEditBoxChar(hWnd, bKeyCode);
	return ret;
}

void UnicodeToUTF_8(char* pOut,wchar_t* pText) {
	
	// 注意 WCHAR高低字的顺序,低字节在前，高字节在后   
    char* pchar = (char *)pText;
    pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
    pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
    pOut[2] = (0x80 | (pchar[0] & 0x3F));
	return;

}   

void __stdcall MultiByteFix(LPSTR str)
{
	struct tagChat {
		DWORD flag0;
		DWORD flag;
		DWORD _1[5];
		char txt[100];
	};
	tagChat *pc = (tagChat*)str;
	if ( fInGame==FALSE && pc->flag !=4 && pc->flag !=10)return ;

	char szTemp[300];
	char *pStr = pc->txt + strlen(pc->txt) + 1;
	char *ptemp = szTemp;
	char *p = pStr;

	//先还原成gb2312
	while( *p ){
		if ( ((*p)&0xFC)==0xC0 ){//汉字
			*ptemp = ((p[0]&0x03)<<6) +(p[1]&0x3F) ;
			p++;
		}else{
			*ptemp = *p;
		}
		p++;
		ptemp++;
	}
	*ptemp ='\0';
	
	//重新转换utf8
	ptemp = szTemp;
	char buf[4];
	wchar_t pbuffer = L'\0';
	while(*ptemp){
		if(*ptemp>0){
			*pStr++ = *ptemp++;
		}else{
			memset(buf,0,4);
			MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,ptemp,2,&pbuffer,1);
			UnicodeToUTF_8(buf , &pbuffer);
			*pStr++ = buf[0];
			*pStr++ = buf[1];
			*pStr++ = buf[2];
			ptemp++;
			ptemp++;
		}
	}
	*pStr= '\0';
}

void __declspec(naked) MultiByteFixPatch_ASM()
{
	__asm {
		mov eax, [p_D2BnChatMessage];
		mov [eax], ebp;
		push ebp;
		call MultiByteFix;
		ret;
	}
}

void __declspec(naked) IsPritableCharacterPatch_ASM()
{
	__asm {
		test cl, 0x80;
		jz oldcode;
		cmp cl, 0xff;
		jz oldcode;
		pop eax; // adjust esp
		mov eax, 1;
		ret;
oldcode:
		movzx ax, cl;
		cmp ax, 0x100
		ret;
	}
}


#endif