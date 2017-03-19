#include "stdafx.h"
#ifdef MODULE_LOCKWINDOW
RECT rcOldClip;

void UnlockWindow(){
	if(rcOldClip.bottom != NULL){
		ClipCursor(&rcOldClip);
	}
}

void LockWindow(){
	if(tLockWindowToggle.isOn || (tMouseScrollMapToggle.isOn &&  nMouseScrollMap ==1)){
		HWND active = GetActiveWindow();
		HWND hwnd = D2GetHwnd(); 
		if(active == hwnd){
			RECT rect ;
			GetWindowRect (hwnd, &rect); 
 			rect.top = rect.top+30;
			rect.left = rect.left+5;
			rect.right = rect.right-5;
			rect.bottom = rect.bottom - 5;
			RECT rc ;
			GetClipCursor(&rc);
			if(rc.bottom != rect.bottom || rc.top!= rect.top || rc.left !=rect.left || rc.right !=rect.right){
				ClipCursor(&rect);
				return;
			}
		}
	}
	UnlockWindow();
	return;
}
#endif
