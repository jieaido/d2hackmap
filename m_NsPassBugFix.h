#ifdef FUNCTION_DECLARE
	#define MODULE_NSPASSBUGFIX
	void NsPassingActBugFixPatch_ASM();
#endif

#ifdef VARIABLE_DEFINE

 
#endif

#ifdef PATH_INSTALL
{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB44704),    (DWORD)NsPassingActBugFixPatch_ASM,       9 ,   &fDefault},//-ns bugfix for d2loader  

#endif

#ifdef CONFIG_LOAD


#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP


#endif


#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif