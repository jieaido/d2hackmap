#ifdef FUNCTION_DECLARE
	#define MODULE_PERMSHOWITEM
	void	PermShowItemsPatch1_ASM();
	void	PermShowItemsPatch2_ASM();
	void	PermShowItemsPatch3_ASM();
	void	PermShowItemsPatch4_ASM();	

#endif

#ifdef VARIABLE_DEFINE

 GVAR2(ToggleVar,	tPermShowItems,				1,	0,	-1,	1,	"Perm show items")
 GVAR2(ToggleVar,	tLockAltToggle,				1,	0,	-1,	1,	"Lock Alt")

#endif

#ifdef PATH_INSTALL
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB16D5E),    (DWORD)PermShowItemsPatch1_ASM,         6 ,   &fDefault},
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB13EBA),    (DWORD)PermShowItemsPatch1_ASM,         6 ,   &fDefault},
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB0DDF3),    (DWORD)PermShowItemsPatch2_ASM,         6 ,   &fDefault},
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB0D9FA),    (DWORD)PermShowItemsPatch3_ASM,         6 ,   &fDefault},
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FAFD233),    (DWORD)PermShowItemsPatch4_ASM,         6 ,   &fDefault},

#endif

#ifdef CONFIG_LOAD
	{1, "PermShowItemsToggle",		&tPermShowItems     },
	{1, "LockAltToggle",			&tLockAltToggle     },

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
