#ifdef FUNCTION_DECLARE
	#define MODULE_SOCKET
	void FixSocketTimeOut_ASM();
	void FixSocketErrRet_ASM();
#endif

#ifdef VARIABLE_DEFINE
GVAR (DWORD,		dwSocketTimeOutSec,		100)
GVAR (DWORD,		dwSocketTimeOut,		100000) 
GVAR (BOOL,			fFixSocketError,		TRUE)
#endif

#ifdef PATH_INSTALL
	{PatchCALL,   DLLOFFSET(D2NET,    0x6FBF6CC2),    (DWORD)FixSocketTimeOut_ASM,				  8 ,   &fDefault},
	{PatchCALL,   DLLOFFSET(D2NET,    0x6FBF6E48),    (DWORD)FixSocketErrRet_ASM,				  10 ,   &fFixSocketError},

#endif

#ifdef CONFIG_LOAD
	{2, "SocketTimeOutValue",  &dwSocketTimeOutSec,4},
	{2, "FixSocketError",	   &fFixSocketError,4},
#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP


#endif


#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE
if ( dwSocketTimeOutSec>100) dwSocketTimeOutSec = 100;
if ( dwSocketTimeOutSec<5) dwSocketTimeOutSec = 5;
dwSocketTimeOut = dwSocketTimeOutSec*1000;

#endif