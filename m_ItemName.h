#ifdef FUNCTION_DECLARE
	#define MODULE_ITEMNAME
	void OpenCubeStringPatch_ASM();
	void ItemNamePatch_ASM();
	BOOL ItemHaveLevel(BYTE nType);
#endif

#ifdef VARIABLE_DEFINE

GVAR (BYTE,			nQuestItemColour,			(BYTE)-1)
GVAR (wchar_t,		wszEtherealItemPrefix[30],  {L'\0'})
GVAR (wchar_t,		wszEtherealItemPostfix[30], {L'\0'})
GVAR (wchar_t,		wszEtherealBugItemPrefix[30],  {L'\0'})
GVAR (wchar_t,		wszEtherealBugItemPostfix[30], {L'\0'})
GVAR2(ToggleVar,	tRuneNumbers,		1,	1,	-1,	1,"Rune numbers")
GVAR2(ToggleVar,	tSocketNumbers,		1,	1,	-1,	1,"Socket numbers")
GVAR2(ToggleVar,	tItemLevel,			1,	0,	-1,	1, 0)
GVAR2(ToggleVar,	tItemValue,			1,	0,	-1,	1, 0)
GVAR2(ToggleVar,	tItemIndex,			1,	0,	-1,	1, 0)
GVAR2(ToggleVar,	tItemFileIndex,		1,	0,	-1,	1, 0)
GVAR2(ToggleVar,	tUnitNumber,		1,	0,	-1,	1, 0)
GVAR2(ToggleVar,	tItemQLevel,		1,	0,	-1,	1, 0)
GVAR2(ToggleVar,	tItemMLevel,		1,	0,	-1,	1, 0)
GVAR2(ToggleVar,	tItemALevel,		1,	0,	-1,	1, 0)
GVAR2(ToggleVar,	tAfterCube,			1,	0,	-1,	1, 0)
GVAR2(ToggleVar,	tLifePerLevel,		1,	0,	-1,	1, 0)
GVAR2(ToggleVar,	tItemType,			1,	0,	-1,	1, 0)
GVAR2(DWORD,		dwItemValueNpc[5],	154,178,255,405,513 )
GVAR2(ToggleVar,	tShowBaseED,				1,	0,	-1,	1 , "Show Base ED")
#endif

#ifdef PATH_INSTALL

  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB26B66),    (DWORD)ItemNamePatch_ASM,               6 ,   &fDefault}, 
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB28C83),    (DWORD)OpenCubeStringPatch_ASM,         5 ,   &fDefault}, 
  {PatchVALUE,  DLLOFFSET(D2CLIENT, 0x6FB1324F),    0xe990,                                 2 ,   &fDefault},  //kill ground gold name

#endif

#ifdef CONFIG_LOAD

  {2, "QuestItemColour",        &nQuestItemColour, 1 },
  {1, "RuneNumbersToggle",      &tRuneNumbers        },
  {1, "SocketNumbersToggle",    &tSocketNumbers      },
  {1, "ItemLevelsToggle",       &tItemLevel       },
  {1, "ItemValueToggle",        &tItemValue       },
  {1, "ItemIndexsToggle",       &tItemIndex       },
  {1, "ItemFileIndexsToggle",   &tItemFileIndex   },
  {1, "UnitNumbersToggle",      &tUnitNumber      },
  {4, "EtherealItemPrefix",     &wszEtherealItemPrefix, 1,  {30 }},
  {4, "EtherealItemPostfix",    &wszEtherealItemPostfix,1,  {30 }},
  {4, "EtherealBugItemPrefix",     &wszEtherealBugItemPrefix, 1,  {30 }},
  {4, "EtherealBugItemPostfix",    &wszEtherealBugItemPostfix,1,  {30 }},
  
  {1, "ItemQLevelToggle",       &tItemQLevel      },
  {1, "ItemMLevelToggle",       &tItemMLevel      },
  {1, "ItemALevelToggle",       &tItemALevel      },
  {1, "ItemAfterCubeToggle",    &tAfterCube       },
  {1, "ItemTypeToggle",			&tItemType       },

  {1, "ItemLifePerLevelToggle", &tLifePerLevel    },
  {1, "ShowBaseEDToggle",           &tShowBaseED      },
#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP


#endif


#ifdef RUN_ENDGAME


#endif

#ifdef INIT_VALUE
  memset( wszEtherealItemPrefix ,    0 ,      sizeof(wszEtherealItemPrefix) );
  memset( wszEtherealItemPostfix ,   0 ,      sizeof(wszEtherealItemPostfix) );
  memset( wszEtherealBugItemPrefix ,    0 ,      sizeof(wszEtherealBugItemPrefix) );
  memset( wszEtherealBugItemPostfix ,   0 ,      sizeof(wszEtherealBugItemPostfix) );


#endif

#ifdef FIX_VALUE


#endif
