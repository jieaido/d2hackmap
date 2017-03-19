#ifdef FUNCTION_DECLARE
	#define MODULE_SCROLLLOCK
	void SetScrollMapPos(char xinc, char yinc);
	void InitScrollLock(BOOL fInit);
	void CenterMap();
	void SetMapShake();
	void DrawScollOffset(wchar_t*wbuf ,int posy);

#endif

#ifdef VARIABLE_DEFINE

GVAR2(ToggleVar,	tDiagonalScroll,		1,	1,	-1,		1 ,"Diagonal scroll Toggle" )
GVAR2(ToggleVar,	tScrollMap,				1,	0,	-1,		1 )
GVAR2(ToggleVar,	tCenterMap,			    2,	0,	-1,		1,	0,		&CenterMap)
GVAR (DWORD,		nMapScrollSpeed,	        16)
GVAR (DWORD,		nScrollMode,				1)
GVAR2(char,			nMapScrollOffset[9][5][2], {0})
GVAR2(ToggleVar,	tMapScrollKey[9]	, 	   {0})

#endif

#ifdef PATH_INSTALL
  
  {PatchFILL,   DLLOFFSET(D2CLIENT, 0x6FB4349F),    INST_NOP,                               2 ,   &fDefault}, //force perspective shake
  {PatchFILL,   DLLOFFSET(D2CLIENT, 0x6FACBDFF),    INST_NOP,                               2 ,   &fDefault}, //force get shake
  {PatchFILL,   DLLOFFSET(D2CLIENT, 0x6FB433C6),    INST_NOP,                               15,   &fDefault}, //kill add shake
  {PatchFILL,   DLLOFFSET(D2CLIENT, 0x6FB433D5),    INST_NOP,                               2 ,   &fDefault}, //kill add shake, part 2
  {PatchFILL,   DLLOFFSET(D2CLIENT, 0x6FAFFE60),    INST_NOP,                               0x37, &fDefault}, //kill automap scroll, wipe out 4 adjustments


#endif

#ifdef CONFIG_LOAD

  {1, "ScrollMapToggle",         &tScrollMap       },
  {1, "DiagonalScrollToggle",    &tDiagonalScroll    },
  {1, "CenterMapScrollKey",      &tCenterMap },
  {2, "ScrollMode",              &nScrollMode      , 4 },
  

  {5, "MapScrollOffset1",        &nMapScrollOffset[1], 2,{5}},
  {5, "MapScrollOffset2",        &nMapScrollOffset[2], 2,{5}},
  {5, "MapScrollOffset3",        &nMapScrollOffset[3], 2,{5}},
  {5, "MapScrollOffset4",        &nMapScrollOffset[4], 2,{5}},
  {5, "MapScrollOffset5",        &nMapScrollOffset[5], 2,{5}},
  {5, "MapScrollOffset6",        &nMapScrollOffset[6], 2,{5}},
  {5, "MapScrollOffset7",        &nMapScrollOffset[7], 2,{5}},
  {5, "MapScrollOffset8",        &nMapScrollOffset[8], 2,{5}},
  {1, "MapScrollKey1",           &tMapScrollKey[1]   },
  {1, "MapScrollKey2",           &tMapScrollKey[2]   },
  {1, "MapScrollKey3",           &tMapScrollKey[3]   },
  {1, "MapScrollKey4",           &tMapScrollKey[4]   },
  {1, "MapScrollKey5",           &tMapScrollKey[5]   },
  {1, "MapScrollKey6",           &tMapScrollKey[6]   },
  {1, "MapScrollKey7",           &tMapScrollKey[7]   },
  {1, "MapScrollKey8",           &tMapScrollKey[8]   },
  
#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP


#endif


#ifdef INIT_VALUE

	InitScrollLock(TRUE);
#endif

#ifdef FIX_VALUE

	InitScrollLock(FALSE);
	#ifdef MODULE_ROOMAREA
	if ( tAutomapScreenArea.key == tScrollMap.key ){
		tAutomapScreenArea.isOn = tScrollMap.isOn ;
	}
	#endif
#endif