
#ifdef FUNCTION_DECLARE
	#define MODULE_PLAYERLIFEBAR
	void PlayerNamePatch_ASM();

#endif

#ifdef VARIABLE_DEFINE

GVAR2(ToggleVar,	tPlayerLevel,				1,	0,	-1,	1, 0)
GVAR2(ToggleVar,	tPlayerDistance,			1,	0,	-1,	1, 0)
GVAR2(ToggleVar,	tPlayerHPPercent,			1,	0,	-1,	1, 0)


#endif

#ifdef PATH_INSTALL
 {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB13EA8),    (DWORD)PlayerNamePatch_ASM,			  5 ,   &fDefault},

#endif

#ifdef CONFIG_LOAD
  {1, "PlayerLevelToggle",       &tPlayerLevel       },
  {1, "PlayerDistanceToggle",    &tPlayerDistance    },
  {1, "PlayerHPPercentToggle",   &tPlayerHPPercent   },

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
