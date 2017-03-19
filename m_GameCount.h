
#ifdef FUNCTION_DECLARE
	#define MODULE_GAMECOUNT
	void KillCountPatch_ASM();
	void ShowGameCount();
	void UnitModeChangePatch_ASM();
#endif

#ifdef VARIABLE_DEFINE
GVAR2(ToggleVar,	tKillCount,				1,	0,	-1,		1, 0,	)
GVAR2(ToggleVar,	tGetHitCount,			1,	0,	-1,		1, 0,	)

GVAR (DWORD,		dwKillSum,				0)
GVAR (DWORD,		dwGameKills,			0)
GVAR (DWORD,		dwLastKills,			0) 

GVAR (DWORD,		dwGetHitSum,			0)
GVAR (DWORD,		dwGetHits,				0)
GVAR (DWORD,		dwOrgMode,				0)
#endif

#ifdef PATH_INSTALL

	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB6EB21),    (DWORD)KillCountPatch_ASM,               6 ,   &fDefault},
	{PatchCALL,   DLLOFFSET(D2COMMON, 0x6FDAF912),    (DWORD)UnitModeChangePatch_ASM,          6 ,   &fDefault},

#endif

#ifdef CONFIG_LOAD

{1,     "KillCountToggle",		&tKillCount         },
{1,     "GetHitCountToggle",	&tGetHitCount         },


#endif


#ifdef RUN_ONCE
dwGetHits = 0;
dwGameKills = 0;
dwLastKills = 0;
#endif

#ifdef RUN_LOOP

dwOrgMode = 0;
#endif


#ifdef RUN_ENDGAME


#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
