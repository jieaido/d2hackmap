
#ifdef FUNCTION_DECLARE
	#define MODULE_GAMEWINDOW
	void KeepWindowPatch();
	void RemoveKeepWindowPatch();
	void NoHidePatch_ASM();
	BOOL IsFullWindow();
#endif

#ifdef VARIABLE_DEFINE
GVAR2(ToggleVar,	tKeepGameWindow,		1,	0,	-1,		1 , "Keep game window",		&KeepWindowPatch)
 GVAR2(ToggleVar,	tNoHide,				1,	0,	-1,		1,	"No Hide")
 GVAR(BOOL  , fFullWindows , 0)
#endif

#ifdef PATH_INSTALL

{PatchCALL,   DLLOFFSET(D2GFX, 0x6FA88379),    (DWORD)NoHidePatch_ASM,               5 ,   &fDefault},
#endif

#ifdef CONFIG_LOAD

	{1, "KeepGameWindowToggle",   &tKeepGameWindow    },
	{1, "NoHideToggle",			  &tNoHide     },		
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
	fFullWindows = IsFullWindow() ;

#endif
