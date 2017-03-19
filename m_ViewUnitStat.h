
#ifdef FUNCTION_DECLARE
	#define MODULE_VIEWUNITSTAT
	void ViewUnitStatPatch_ASM();
	void ViewPetStatPatch_ASM();
	void SwitchStatPage(int nStep);
#endif

#ifdef VARIABLE_DEFINE
GVAR2(ToggleVar,	tShowBaseStat,				1,	1,	-1,	1 , "Show Player Base Stat")
GVAR2(ToggleVar,	tFirstPlayerStat,			3,	0,	-1,	1 , 0, &SwitchStatPage		,0)
GVAR2(ToggleVar,	tNextPlayerStat,			3,	0,	-1,	1 , 0, &SwitchStatPage		,1)
GVAR2(ToggleVar,	tPrevPlayerStat,			3,	0,	-1,	1 , 0, &SwitchStatPage		,-1)
#endif

#ifdef PATH_INSTALL
{PatchJMP,    DLLOFFSET(D2CLIENT, 0x6FB3A0B6),    (DWORD)ViewUnitStatPatch_ASM,         10 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB2F4FC),    (DWORD)ViewPetStatPatch_ASM,          6 ,   &fDefault},//petœ‘ æ
#endif

#ifdef CONFIG_LOAD
  {1, "FirstPlayerStatKey",     &tFirstPlayerStat   },
  {1, "NextPlayerStatKey",      &tNextPlayerStat    },
  {1, "PreviousPlayerStatKey",  &tPrevPlayerStat    },
  {1, "ShowBaseStat",           &tShowBaseStat      },

#endif


#ifdef RUN_ONCE
SwitchStatPage(0);

#endif

#ifdef RUN_LOOP


#endif


#ifdef RUN_ENDGAME


#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
