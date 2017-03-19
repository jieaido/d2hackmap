#ifdef FUNCTION_DECLARE

	#define MODULE_ITEMDESC
	void ItemBasicStatPatch_ASM();
	void ItemSocketViewPatch_ASM();
	void SocketItemStatViewPatch_ASM();
	void __fastcall ItemDescPath( wchar_t *wszMsg , int xpos , int ypos , int tran, int color );
	StatList * __stdcall GetItemExtStatListPatch(UnitAny *pUnit, DWORD dwStatNo, DWORD dwListFlag) ;

	
#endif

#ifdef VARIABLE_DEFINE

	GVAR2(ToggleVar,	tItemBasicStat,				1,	0,	-1,	1 , "Item basic stat")
	GVAR2(ToggleVar,	tViewSocketable,			1,	0,	-1,	1 , "View socketables")
	GVAR2(ToggleVar,	tViewSocketBase,			1,	0,	-1,	1 , "View socketed base")
	

#endif

#ifdef PATH_INSTALL

	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FAD22FD),    (DWORD)ItemBasicStatPatch_ASM,          5 ,   &fDefault},
	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FAD22D7),    (DWORD)GetItemExtStatListPatch,         5 ,   &fDefault},
	
	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB27C50),    (DWORD)ItemSocketViewPatch_ASM,         5 ,   &fDefault},
    {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB27BE2),    (DWORD)SocketItemStatViewPatch_ASM,     5 ,   &fDefault},//镶嵌的物品只显示有效属性
	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB283E2),    (DWORD)ItemDescPath,                    5 ,   &fDefault},
	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB2840A),    (DWORD)ItemDescPath,                    5 ,   &fDefault},
	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB27B55),    (DWORD)ItemDescPath,                    5 ,   &fDefault},

#endif

#ifdef CONFIG_LOAD

  {1, "ViewSocketablesToggle",		&tViewSocketable    },
  {1, "ItemBasicStatsToggle",		&tItemBasicStat     },
  {1, "ViewSocketBaseItemsToggle",  &tViewSocketBase    },


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
