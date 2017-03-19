#include "stdafx.h"

#ifdef MODULE_NSPASSBUGFIX

void __declspec(naked) NsPassingActBugFixPatch_ASM()
{
		__asm {
		test edi, edi;
		jz retcode;
//oldcode
		rep stosd;
		mov ecx, edx;
		and ecx, 3;
		rep stosb;
retcode:
		ret;
	}
}


#endif