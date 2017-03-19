
#ifdef FUNCTION_DECLARE
	#define MODULE_PARTYINFO
	void DrawPetHeadPath_ASM();
	void DrawPartyHeadPath_ASM();
#endif

#ifdef VARIABLE_DEFINE
	GVAR2(ToggleVar,	tShowPartyPosition,				1,	0,	-1,	1,	0)
	GVAR2(ToggleVar,	tShowPartyLevel,				1,	0,	-1,	1,	0)
#endif

#ifdef PATH_INSTALL

{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB1B472),    (DWORD)DrawPetHeadPath_ASM,            7 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB1BDA0),    (DWORD)DrawPartyHeadPath_ASM,          6 ,   &fDefault},
#endif

#ifdef CONFIG_LOAD

{1, "ShowPartyPositionToggle",		&tShowPartyPosition     },
{1, "ShowPartyLevelToggle",			&tShowPartyLevel		},

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
