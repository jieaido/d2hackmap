
#ifdef FUNCTION_DECLARE
	#define MODULE_QUESTPROTECT
	void DrawQuestPagePatch_ASM();
	void ReSetTimer();
	void InitBugInfo();
	void SetBugQuestStatus();
	void ShowBugInfo() ;
	void RecvCommand_5D_Patch_ASM();
	void RecvCommand_89_Patch_ASM();
	void CheckUnitKM();
#endif

#ifdef VARIABLE_DEFINE

GVAR2(ToggleVar,	tBugKM,				1,	0,	-1,	1, "Bug KM Protect" , &ReSetTimer)
GVAR2(ToggleVar,	tBugKD,				1,	0,	-1,	1, "Bug KD Protect" , &ReSetTimer)
GVAR2(ToggleVar,	tBugKB,				1,	0,	-1,	1, "Bug KB Protect" , &ReSetTimer)
GVAR2(ToggleVar,	tBugAutoQuit,	    1,	1,	-1,	1, "Bug Auto Quit Toggle"	,&ReSetTimer)
GVAR (DWORD,		dwBugAlertTimes,			10)
GVAR2(ToggleVar,	tAlertNoBug,		1,	1,	-1,	1, 0)
GVAR (DWORD,		dwBugProtectLvl,			0)
#endif

#ifdef PATH_INSTALL
{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB58DC9),    (DWORD)DrawQuestPagePatch_ASM,          6 ,   &fDefault},

{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB70A60),   (DWORD)RecvCommand_5D_Patch_ASM,        5 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB5F8D0),   (DWORD)RecvCommand_89_Patch_ASM,        5 ,   &fDefault},

#endif

#ifdef CONFIG_LOAD
  {1, "BugKMToggle",          &tBugKM         },
  {1, "BugKDToggle",          &tBugKD         },
  {1, "BugKBToggle",          &tBugKB         },
  {1, "BugAutoQuitToggle",    &tBugAutoQuit   },
  {2, "BugAlertTimes",        &dwBugAlertTimes ,4 },
  {1, "AlertNoBug",           &tAlertNoBug    },
  {2, "BugProtectDifficulty", &dwBugProtectLvl ,4 },
#endif


#ifdef RUN_ONCE

SetBugQuestStatus();
#endif

#ifdef RUN_LOOP
CheckUnitKM();
ShowBugInfo();

#endif


#ifdef RUN_ENDGAME


#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE
InitBugInfo();

#endif
