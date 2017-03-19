#include "stdafx.h"

#ifdef MODULE_ROOMINFO

static DWORD nTickCount;

void SetTickCount()
{
	nTickCount = GetTickCount();
}

void __fastcall DrawGameInfoPatch(DWORD dwFont) {

	wchar_t wbuf[512];
	int ypos = INFOY;
	DWORD dwOldFone = D2SetTextFont(8);
	if (tLayerLevelNo.isOn) {

		wsprintfW(wbuf, L"Layer No: %d", LAYER->dwLayerNo);
		DrawDefaultFontText(wbuf ,	INFOX , ypos , 4 , 0 );
		ypos += 16;

		wsprintfW(wbuf, L"Level No: %d", LEVELNO);
		DrawDefaultFontText(wbuf ,	INFOX , ypos , 4 , 0 );
		ypos += 16;

	}
	
	if (tAreaLevel.isOn) {

		wsprintfW(wbuf, L"Area Level: %d", GetAreaLevel());
		DrawDefaultFontText(wbuf ,	INFOX , ypos , 4 , 0 );
		ypos += 16;

	}
	
	if ( tClock.isOn ) {

		SYSTEMTIME t;
		GetLocalTime(&t);
		wsprintfW(wbuf, L"%.2d:%.2d:%.2d", t.wHour, t.wMinute, t.wSecond );
		DrawDefaultFontText(wbuf ,	INFOX , ypos , 4 , 0 );
		ypos += 16;

	}
	if (tGameTime.isOn) {

		DWORD secs = (GetTickCount() - nTickCount)/1000;
		wsprintfW(wbuf, L"%.2d:%.2d:%.2d", secs/3600, (secs/60)%60, secs%60);
		DrawDefaultFontText(wbuf ,	INFOX , ypos , 4 , 0 );
		ypos += 16;

	}

	if (tServerIp.isOn && GAMEINFO->szGameServerIp[0] )
	{
		wsprintfW2(wbuf, "%s", GAMEINFO->szGameServerIp);
		DrawDefaultFontText(wbuf ,	INFOX , ypos , 4 , 0 );
		ypos += 16;

	}
	
	mYposOffset = ypos + 48;

	#ifdef MODULE_SCROLLLOCK
		DrawScollOffset(wbuf,ypos);
	#endif
	D2SetTextFont(dwOldFone);
	D2SetTextFont(dwFont);

}


void __declspec(naked) FixBodyImageOffset_ASM()
{
  __asm
  {
    mov esi ,[mYposOffset]
    ret
  }
}




#endif