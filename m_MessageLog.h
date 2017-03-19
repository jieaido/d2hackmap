
#ifdef FUNCTION_DECLARE
	#define MODULE_MESSAGELOG
	void MessageLogPatch1_ASM();
	void MessageLogPatch2_ASM();
	void LogExitMessage();
#endif

#ifdef VARIABLE_DEFINE

 GVAR2(ToggleVar,	tLogMessage,		1,	0,	-1,	1,0)
 GVAR (DWORD,		dwMessageFileSize,		1048576)
#endif

#ifdef PATH_INSTALL
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FAC67DD),    (DWORD)MessageLogPatch1_ASM,            6 ,   &fDefault},
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FAC65A3),    (DWORD)MessageLogPatch2_ASM,            5 ,   &fDefault},

#endif

#ifdef CONFIG_LOAD

  {1, "MessageLogToggle",    &tLogMessage},
  {2, "MessageLogFileSize",  &dwMessageFileSize,4},
#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP


#endif


#ifdef RUN_ENDGAME
	LogExitMessage();

#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
