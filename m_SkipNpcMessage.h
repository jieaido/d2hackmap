
#ifdef FUNCTION_DECLARE
	#define MODULE_SKIPNPCMESSAGE
	void NPCQuestMessageStartPatch_ASM();
	void NPCQuestMessageEndPatch1_ASM();
	void NPCQuestMessageEndPatch2_ASM();
	void NPCMessageLoopPatch_ASM();
#endif

#ifdef VARIABLE_DEFINE

	GVAR (DWORD,		mSkipQuestMessage,			0)

#endif

#ifdef PATH_INSTALL

  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB0C9B7),    (DWORD)NPCQuestMessageStartPatch_ASM,           6 ,   &fDefault},
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB09586),    (DWORD)NPCQuestMessageEndPatch1_ASM,            8 ,   &fDefault},
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB08A9F),    (DWORD)NPCQuestMessageEndPatch2_ASM,            5 ,   &fDefault},
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FAC7D77),    (DWORD)NPCMessageLoopPatch_ASM,					6 ,   &fDefault},
#endif

#ifdef CONFIG_LOAD
	{2, "SkipQuestMessage",   &mSkipQuestMessage,   4},

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
