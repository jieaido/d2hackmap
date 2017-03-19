#ifdef FUNCTION_DECLARE
#define MODULE_AUTOMAP
void RevealAutomap();
void ResetMapStatus();	
void ShowAutoMap();
void RevealLevelPlayerIn();
#endif

#ifdef VARIABLE_DEFINE
GVAR (BOOL,			fAutoRevealAct,			0)

GVAR2(ToggleVar,	tRevealAct,				2,	0,	-1,		1,  0,			&RevealAutomap)
GVAR2(ToggleVar,	tRevealLevel,			2,	0,	-1,		1,  0,			&RevealLevelPlayerIn)
GVAR2(ToggleVar,	tAutoMap,				1,	1,	-1,		1, "Auto Map Toggle"	)

#endif

#ifdef PATH_INSTALL


#endif

#ifdef CONFIG_LOAD
 {1, "RevealActAutomapKey",      &tRevealAct       },
 {1, "RevealLevelAutomapKey",    &tRevealLevel     },
 {1, "AutoMapToggle",            &tAutoMap         },
 {2, "AutoRevealAct",            &fAutoRevealAct   ,  4 },

#endif


#ifdef RUN_ONCE

ResetMapStatus();
ShowAutoMap();

#endif

#ifdef RUN_LOOP

 RevealAutomap();

#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif