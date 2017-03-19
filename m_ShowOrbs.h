#ifdef FUNCTION_DECLARE
	#define MODULE_SHOWORBS
	void PermShowLifePatch_ASM();
	void PermShowOrbPatch_ASM();
	void PermShowManaPatch_ASM();
#endif

#ifdef VARIABLE_DEFINE
GVAR2(ToggleVar,	tPermShowOrb,		1,	1,	-1,	1, "Perm Show Life/Mana")

#endif

#ifdef PATH_INSTALL

	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB65DF3),    (DWORD)PermShowLifePatch_ASM,           5 ,   &fDefault},
	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB65EDB),    (DWORD)PermShowOrbPatch_ASM,            11,   &fDefault},
	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB65EE6),    (DWORD)PermShowManaPatch_ASM,           6 ,   &fDefault},

#endif

#ifdef CONFIG_LOAD
{1, "PermShowOrbsToggle",    &tPermShowOrb       },

#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP


#endif


#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif