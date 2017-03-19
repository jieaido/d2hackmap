#include "stdafx.h"

#ifdef MODULE_GAMEWINDOW

BOOL fKeepWindowPatch = FALSE;
static Patch_t aKeepGameWindowPatchs[] = {
    {PatchFILL,   DLLOFFSET(D2GFX, 0x6FA88381),     4,    1,    &fDefault}, // SW_MINIMIZE
    {PatchFILL,   DLLOFFSET(D2GFX, 0x6FA87EA7),     4,    1,    &fDefault}, // SW_HIDE
};


BOOL IsFullWindow()
{
  WINDOWINFO wi;
  HWND hwnd = D2GetHwnd();
  if (hwnd && GetWindowInfo(hwnd, &wi)) {
    if ( (wi.dwStyle & WS_CAPTION) && (wi.dwExStyle& WS_EX_WINDOWEDGE) ) {
      return false;
    }
  }
  else {
    LPSTR pszCmdLine = GetCommandLine();
    LPSTR p;
    for ( p = pszCmdLine; (p=strchr(p, ' ')) != NULL; p++) {
      if ((p[1] == '-') &&
        (p[2] == 'w' || p[2] == 'W') &&
        (p[3] == ' ' || p[3] == '\0')) {
        return false;
      }
    }
  }
  return true;
}


void KeepWindowPatch()
{
  if( fKeepWindowPatch ){
    RemoveD2Patchs(aKeepGameWindowPatchs, aKeepGameWindowPatchs+_ARRAYSIZE(aKeepGameWindowPatchs));
    fKeepWindowPatch = 0;
  }
  if (tKeepGameWindow.isOn && !fFullWindows){
    InstallD2Patchs(aKeepGameWindowPatchs, aKeepGameWindowPatchs+_ARRAYSIZE(aKeepGameWindowPatchs));
    fKeepWindowPatch = 1;
  }
}


void RemoveKeepWindowPatch(){

	if( fKeepWindowPatch ){
		RemoveD2Patchs(aKeepGameWindowPatchs, aKeepGameWindowPatchs+_ARRAYSIZE(aKeepGameWindowPatchs));
		fKeepWindowPatch = 0;
	  }
  
}

void __declspec(naked) NoHidePatch_ASM()
{
	__asm{
		cmp [fFullWindows] , 0
		jne nodraw

		cmp [tNoHide.isOn] , 0
		je nodraw

		xor eax , eax
		jmp justret
nodraw:
		test eax , eax
justret:
		push ecx
		mov ecx ,[p_D2WinState]
		mov [ecx] , eax
		pop ecx
		ret 
	}
}

#endif