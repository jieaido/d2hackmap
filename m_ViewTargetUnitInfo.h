
#ifdef FUNCTION_DECLARE
	#define MODULE_VIEWTARGETUNITINFO
	void GetViewingStatsPlayerPatch1_ASM();
	void GetViewingStatsPlayerPatch2_ASM();
	UnitAny* GetViewStatUnit();
	UnitAny*  GetViewEquUnit();
	void SetViewUnit();
	void ViewUnit(int nType);

	void GetUnitDrawEquipItemPatch_ASM();
	void GetUnitDrawItemDescPath_ASM();
	void GetUnitTestHasItem_ASM();
	void GetUnitDrawInvItemPatch_ASM();
	void GetUnitProtectClickEquipPatch_ASM();
	void GetUnitProtectClickInvPatch_ASM();
#endif

#ifdef VARIABLE_DEFINE

 GVAR2(ToggleVar,	tViewEquipmentKey,	    3,	0,	-1,  1,	0, &ViewUnit ,UIVAR_INVENTORY)
 GVAR2(ToggleVar,	tViewPlayerStatsKey,    3,	0,	-1,	 1, 0, &ViewUnit ,UIVAR_STATS)
#endif

#ifdef PATH_INSTALL

  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB39326),    (DWORD)GetViewStatUnit,                 5 ,   &fDefault}, //draw stat
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB39BE3),    (DWORD)GetViewStatUnit,                 5 ,   &fDefault}, //draw stat
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB39023),    (DWORD)GetViewStatUnit,                 5 ,   &fDefault}, //draw stat
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FAEDFC3),    (DWORD)GetViewingStatsPlayerPatch1_ASM, 6 ,   &fDefault}, //drawstat
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB38A04),    (DWORD)GetViewingStatsPlayerPatch2_ASM, 6 ,   &fDefault}, //draw stat

  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB29B72),    (DWORD)GetUnitDrawEquipItemPatch_ASM,   6 ,   &fDefault}, //draw equip items
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB29244),    (DWORD)GetUnitDrawItemDescPath_ASM,     6 ,   &fDefault}, //desc item
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB2826F),    (DWORD)GetUnitTestHasItem_ASM,          5 ,   &fDefault}, //test has item for desc item
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB2EBC5),    (DWORD)GetUnitDrawInvItemPatch_ASM,     5 ,   &fDefault}, //draw inv items

  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB2D650),    (DWORD)GetUnitProtectClickEquipPatch_ASM, 5 ,   &fDefault}, //protect click equip
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB2D5BB),    (DWORD)GetUnitProtectClickInvPatch_ASM, 7 ,   &fDefault}, //protect click inv
  

#endif

#ifdef CONFIG_LOAD

  {1, "ViewEquipmentKey",      &tViewEquipmentKey    },
  {1, "ViewPlayerStatsKey",    &tViewPlayerStatsKey  },

#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP
SetViewUnit();

#endif


#ifdef RUN_ENDGAME


#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
