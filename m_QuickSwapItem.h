
#ifdef FUNCTION_DECLARE
	#define MODULE_QUICKSWAPITEM

	void RButtonUpHandlerPatch_ASM();
	void RButtonInTradePatch_ASM();

	void CtrlClickHandlerPatch_ASM();
	void LButtonUpHandlerPatch_ASM();
	
	void DealCtrlClick();
#endif

#ifdef VARIABLE_DEFINE

    GVAR2(ToggleVar,	tRightClickSwap,    1,	1,	-1,	1 ,	"Right Click Swap")
	GVAR2(ToggleVar,	tCtrlClickSwap,     1,	0,	-1,	1 ,	"Ctrl Click Swap")
	GVAR2(ToggleVar,	tQuickDropToggle,	1,	0,	-1,	1 , "Quick Drop")

#endif

#ifdef PATH_INSTALL

  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FAE27F0),    (DWORD)RButtonUpHandlerPatch_ASM,       5 ,   &fDefault}, 
  {PatchJMP,    DLLOFFSET(D2CLIENT, 0x6FB20066),    (DWORD)RButtonInTradePatch_ASM,         5 ,   &fDefault}, 
	
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB2B5DE),    (DWORD)CtrlClickHandlerPatch_ASM,       6 ,   &fDefault}, 
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB2FD29),    (DWORD)LButtonUpHandlerPatch_ASM,       5 ,   &fDefault}, //家里箱子和身上箱子之间
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB2F804),    (DWORD)LButtonUpHandlerPatch_ASM,       5 ,   &fDefault}, //cube和身上箱子之间
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB30E6F),    (DWORD)LButtonUpHandlerPatch_ASM,       5 ,   &fDefault}, //左边空地和身上箱子之间
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB30146),    (DWORD)LButtonUpHandlerPatch_ASM,       5 ,   &fDefault}, //交易界面和身上箱子之间

#endif

#ifdef CONFIG_LOAD
  {1, "RightClickSwapToggle",  &tRightClickSwap   },
  {1, "CtrlClickSwapToggle",   &tCtrlClickSwap    },
  {1, "QuickDropToggle",       &tQuickDropToggle  },
#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP

DealCtrlClick();
#endif


#ifdef RUN_ENDGAME


#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
