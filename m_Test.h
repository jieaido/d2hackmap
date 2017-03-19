#ifdef FUNCTION_DECLARE
	#define MODULE_TEST
	void ShowTestInfo();
#endif

#ifdef VARIABLE_DEFINE
GVAR2(ToggleVar,	tTestInfo,				2,	0,	-1,		1, 0,			&ShowTestInfo)
 
#endif

#ifdef PATH_INSTALL


#endif

#ifdef CONFIG_LOAD
{1, "TestKey",					&tTestInfo         },

#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP


#endif


#ifdef RUN_ENDGAME


#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
