#ifdef FUNCTION_DECLARE
	#define MODULE_IMEPROTECT
	void ToggleIMEInput(BOOL fEnable);
#endif

#ifdef VARIABLE_DEFINE

 
#endif

#ifdef PATH_INSTALL


#endif

#ifdef CONFIG_LOAD


#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP
ToggleIMEInput(D2CheckUiStatus(UIVAR_CHATINPUT));

#endif


#ifdef RUN_ENDGAME
ToggleIMEInput(1);

#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
