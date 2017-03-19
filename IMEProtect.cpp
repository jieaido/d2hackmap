#include "stdafx.h"
#ifdef MODULE_IMEPROTECT

static BOOL fDisabled = FALSE;
#pragma   comment(lib,"imm32.lib")   
void ToggleIMEInput(BOOL fEnable){

	static HIMC hIMC = NULL; 
	if ( fEnable ){
		if ( fDisabled ) {
			ImmAssociateContext(D2GetHwnd(), hIMC); 
			fDisabled = FALSE;
		}
	}else{
		if ( fDisabled == FALSE ){
			hIMC = ImmAssociateContext(D2GetHwnd(), NULL); 
			fDisabled = TRUE;
		}
	}

}
#endif