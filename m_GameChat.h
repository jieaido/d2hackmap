
#ifdef FUNCTION_DECLARE
	#define MODULE_GAMECHAT
	void WisperPatch_ASM();
	void InputLinePatch1_ASM();
	void InputLinePatch2_ASM();
	void CheckD2WinEditBox();
	void SelectTextPatch1_ASM();
	void SelectTextPatch2_ASM();
#endif

#ifdef VARIABLE_DEFINE

 GVAR2(ToggleVar,	tWisperNotice,				1,	0,	-1,	1, "Wisper Notice")
 GVAR2(ToggleVar,	tInputLine,					1,	1,	-1,	1, "Input line Patch")
 GVAR2(ToggleVar,	tUseCustomFont,				1,	0,	-1,	1, "Use Custom Font")
 GVAR (D2EditBox*,	pD2WinEditBox,				0)
#endif

#ifdef PATH_INSTALL
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB40FF7),    (DWORD)WisperPatch_ASM,                 5 ,   &fDefault},
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB41D9C),    (DWORD)InputLinePatch1_ASM,             5 ,   &fDefault},
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB414AB),    (DWORD)InputLinePatch2_ASM,             5 ,   &fDefault},
  {PatchVALUE,  DLLOFFSET(D2CLIENT, 0x6FAD4605),     0x2EB58,                               3 ,   &fDefault}, 
  {PatchVALUE,  DLLOFFSET(D2CLIENT, 0x6FAD4585),     0x2EB58,                               3 ,   &fDefault},
  {PatchCALL,   DLLOFFSET(D2WIN ,   0x6F8F24A1),     (DWORD)SelectTextPatch1_ASM,			8 ,   &fDefault}, //聊天框选中中文文字
  {PatchCALL,   DLLOFFSET(D2WIN ,   0x6F8F2442),     (DWORD)SelectTextPatch2_ASM,			8 ,   &fDefault}, //聊天框选中中文文字
#endif

#ifdef CONFIG_LOAD
	{1, "WisperNoticeToggle",     &tWisperNotice      },
	{1, "InputLineToggle",        &tInputLine         },
	{1, "UseCustomFontToggle",    &tUseCustomFont     },
#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP

CheckD2WinEditBox();
#endif


#ifdef RUN_ENDGAME

		if (pD2WinEditBox) {
			*(DWORD*)p_D2LastChatMessage = 0;
			wchar_t *p = wcscpy(p_D2LastChatMessage, D2GetEditBoxText(pD2WinEditBox));
			*p_D2ChatTextLength = wcslen(p);
			D2DestroyEditBox(pD2WinEditBox);
			pD2WinEditBox = NULL;
			FOCUSECONTROL = NULL;
		}

#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
