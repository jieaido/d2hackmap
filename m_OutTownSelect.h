
#ifdef FUNCTION_DECLARE
	#define MODULE_OUTTOWNSELECT
	void OutTownSelectPatch_ASM1();
	void OutTownSelectPatch_ASM2();
#endif

#ifdef VARIABLE_DEFINE
GVAR2(ToggleVar,	tOutTownSelect,				1,	1,	-1,	1,	"Out of town select")
 
#endif

#ifdef PATH_INSTALL
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FAFCFD1),    (DWORD)OutTownSelectPatch_ASM1,         6 ,   &fDefault},
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FACFB3B),    (DWORD)OutTownSelectPatch_ASM2,         6 ,   &fDefault},

#endif

#ifdef CONFIG_LOAD
{1, "OutTownSelectToggle",    &tOutTownSelect     },

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
