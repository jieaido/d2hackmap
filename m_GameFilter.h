#ifdef FUNCTION_DECLARE
	#define MODULE_GAMEFILTER
	void D2MCPPacketHandler_05_Patch_ASM();
	void CreateGameBoxPatch_ASM();
	void __stdcall DestroyGamelistPatch( D2EditBox* pListBox );
	void GameListRefreshTimePatch_ASM();
	void DrawGameListPatch_ASM();
#endif

#ifdef VARIABLE_DEFINE

  GVAR (BOOL,			fGameFilter,		FALSE)
#endif

#ifdef PATH_INSTALL

	{PatchCALL,   DLLOFFSET(D2WIN ,		 0x6F8F3E51),   (DWORD)DrawGameListPatch_ASM,           5,   &fGameFilter},

#endif

#ifdef PATH_INSTALL2
	
    {PatchCALL,   DLLOFFSET(D2MCPCLIENT, 0x6FA26380),   (DWORD)D2MCPPacketHandler_05_Patch_ASM,     5 ,   &fGameFilter},
	{PatchCALL,   DLLOFFSET(D2MULTI,	 0x6F9E48CF),   (DWORD)CreateGameBoxPatch_ASM,				5 ,   &fGameFilter},
	{PatchCALL,   DLLOFFSET(D2MULTI,	 0x6F9E1CA3),   (DWORD)DestroyGamelistPatch,				5 ,   &fGameFilter},
	{PatchCALL,   DLLOFFSET(D2MULTI,	 0x6F9DDB4E),   (DWORD)GameListRefreshTimePatch_ASM,		7 ,   &fGameFilter},
	
#endif

#ifdef CONFIG_LOAD

{2, "GameFilterSupport",     &fGameFilter,  4},

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
