
#ifdef FUNCTION_DECLARE
	#define MODULE_QUICKGAME
	void QuickNextGame(int addnum);
	void SaveGameName();
	void QuickExitGame();
	void __fastcall NextGameNamePatch(D2EditBox* box, BOOL (__stdcall *FunCallBack)(D2EditBox*,DWORD,char*));
	void __fastcall NextGamePasswordPatch(D2EditBox* box, BOOL (__stdcall *FunCallBack)(D2EditBox*,DWORD,char*));
#endif

#ifdef VARIABLE_DEFINE

GVAR2(ToggleVar,	tExitGame,			2,	0,	-1,	 1, 	0,	&QuickExitGame,	0)
GVAR2(ToggleVar,	tQuickNextGame,		3,	0,	-1,	 1, 	0,	&QuickNextGame,	1)
GVAR2(ToggleVar,	tQuickNextGame2,	3,	0,	-1,	 1, 	0,	&QuickNextGame,	2)

GVAR2(wchar_t,		wszGameName[32]	,			{L'\0'})
GVAR2(wchar_t,		wszGamePassword[32]	,		{L'\0'})
GVAR (BOOL,			fAutoNextGameName,				0)
GVAR (BOOL,			fAutoNextGamePassword,			0)
GVAR (BOOL,			fCanExitGame,				FALSE)
#endif

#ifdef PATH_INSTALL


#endif

#ifdef PATH_INSTALL2

	{PatchCALL,   DLLOFFSET(D2MULTI, 0x6F9E48EB),   (DWORD)NextGameNamePatch,           5 ,   &fDefault},
    {PatchCALL,   DLLOFFSET(D2MULTI, 0x6F9E4926),   (DWORD)NextGamePasswordPatch,       5 ,   &fDefault},
    {PatchCALL,   DLLOFFSET(D2MULTI, 0x6F9E4C09),   (DWORD)NextGameNamePatch,           5 ,   &fDefault},
    {PatchCALL,   DLLOFFSET(D2MULTI, 0x6F9E4C44),   (DWORD)NextGamePasswordPatch,       5 ,   &fDefault},

#endif


#ifdef CONFIG_LOAD

  {1, "QuickExitGameKey",      &tExitGame              },
  {1, "QuickNextGameKey",      &tQuickNextGame         },
  {1, "QuickNextGameKey2",     &tQuickNextGame2        },

  {2, "AutoNextGameName",      &fAutoNextGameName  ,     4 },
  {2, "AutoNextGamePassword",  &fAutoNextGamePassword  , 4 },
  
  {4, "DefaultGameName",       &wszGameName,     1,  {32 }},
  {4, "DefaultGamePassword",   &wszGamePassword, 1,  {32 }},


#endif


#ifdef RUN_ONCE

SaveGameName();
fCanExitGame = TRUE;
#endif

#ifdef RUN_LOOP


#endif


#ifdef RUN_ENDGAME
fCanExitGame = FALSE;

#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
