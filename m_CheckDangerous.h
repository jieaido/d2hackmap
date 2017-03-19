#ifdef FUNCTION_DECLARE
	#define MODULE_CHECKDANGEROUS
	void ChickenLife();
	void CheckDangerousPlayer( UnitAny  *pUnit );
	void CheckDangerousMonster( UnitAny  *pUnit );
#endif

#ifdef VARIABLE_DEFINE
GVAR (BOOL,			fLifeProtectOn,			FALSE)
GVAR (BOOL,			fDangerousMonsterActive,FALSE)
GVAR (DWORD,		dwChickenLife,						0)
GVAR (DWORD,		dwChickenHostileLife,				0)
GVAR (DWORD,		dwChickenHostileNearbyLife,			0)
GVAR (DWORD,		dwChickenLifePercent,				0)
GVAR (DWORD,		dwChickenHostileLifePercent,		0)
GVAR (DWORD,		dwChickenHostileNearbyLifePercent,	0)
GVAR (DWORD,		nChickenLifeAction,					1)
GVAR2(ToggleVar,	tChickenLife,			1,	0,	-1,	1,	"Chicken life")
GVAR2(ToggleVar,	tChickenHostile,		1,	0,	-1,	1,	"Chicken hostile")
GVAR2(ToggleVar,	tChickenHostileNearby,	1,	0,	-1,	1,	"Chicken hostile nearby")
GVAR2(ToggleVar,	tChickenDangerousMonster,		1,	0,	-1,	1, "Chicken Dangerous Monster")
GVAR2(char,			anDangerousMonster[1000][2]	,		{0})
GVAR (DWORD,		nDangerousMonsterAction,			2)

#endif

#ifdef PATH_INSTALL


#endif

#ifdef CONFIG_LOAD

  {1, "ChickenLifeToggle",          &tChickenLife     },
  {1, "ChickenHostileToggle",		&tChickenHostile    },
  {1, "ChickenHostileNearbyToggle", &tChickenHostileNearby  },
  {2, "ChickenLife",				&dwChickenLife,     4},
  {2, "ChickenHostileLife",			&dwChickenHostileLife,  4},
  {2, "ChickenHostileNearbyLife",   &dwChickenHostileNearbyLife,4},
  {2, "ChickenLifePercent",			&dwChickenLifePercent,  4},
  {2, "ChickenHostileLifePercent",  &dwChickenHostileLifePercent,4},
  {2, "ChickenHostileNearbyLifePercent", &dwChickenHostileNearbyLifePercent,4},
  {2, "ChickenLifeAction",          &nChickenLifeAction,  4},
  {5, "DangerousMonster",           &anDangerousMonster,  2,{1000}},
  {1, "DangerousMonsterChickenToggle", &tChickenDangerousMonster},
  {2, "DangerousMonsterAction",     &nDangerousMonsterAction, 4},

#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP
	ChickenLife();

#endif


#ifdef RUN_ENDGAME


#endif

#ifdef INIT_VALUE
memset(anDangerousMonster,    0,        sizeof(anDangerousMonster));

#endif

#ifdef FIX_VALUE


#endif
