
#ifdef FUNCTION_DECLARE
	
void GameLoopPatch_ASM();
void GameEndPatch_ASM();
void KeyupPatch_ASM();
void KeydownPatch_ASM();
void MButtonDownPatch_ASM();


#endif

#ifdef VARIABLE_DEFINE
	GVAR (BOOL,			fInGame,				FALSE)
	GVAR (BOOL,			fPlayerInTown,			TRUE)
	GVAR (DWORD,		dwCurrentAct,				0)
	GVAR (DWORD,		dwCurrentLevel,				1)
	GVAR (BOOL,			fDefault,			    TRUE)
	GVAR (BOOL,			fKeyRepeat,				FALSE)
	GVAR (DWORD,		dwKeyDown,					0)
	GVAR (int,			dwGameLng,					-1)
	GVAR (DWORD,		dwPlayerId,					0)
	
	
	GVAR (BOOL,			fEnterGameSound,				0)
	GVAR2(DWORD,		actlvls[],	1, 40, 75, 103, 109, 137 )
	
	GVAR2(ToggleVar,	tReloadConfig,			2,	0,	-1,		1, 0,			&ReloadConfig)
	
	GVAR2(char,			szCFGVersion[2][256]	,		{'\0'})
	GVAR2(wchar_t,		wszCFGVersion[2][256]	,		{L'\0'})
	GVAR (char,			aszUnitBlobFiles[12][50],       {'\0'})

	GVAR2 (CellFile*,	pUnitBlobCells[130],	{NULL,})
	GVAR2 (CellFile*,	apMyShrineCells[2][NUMOF_SHRINES],	{0})
	GVAR (CellFile*,	pWaypointCell,						0)
	GVAR (CellFile*,	pMinimapObjectCell,				    0)
	//fanss add
	GVAR (CellFile*,	pMousePosCell,				    0)
	
	GVAR (DWORD,		fShowCheckInfo,					1)
	GVAR (BYTE,			fAutomapPartyDefault,			1)
	GVAR (BYTE,			fAutomapNamesDefault,			1)
    
	GVAR (BOOL,			fLanguageCheck,			TRUE)
	GVAR (BOOL,			fLocalizationSupport,		FALSE)
	GVAR (BOOL,			fAutoSetCHISupport,		1)
	
	GVAR (char,			aszItemBlobFiles[120][50],       {'\0'})


#endif


#ifdef PATH_INSTALL
	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FAE2B40),    (DWORD)GameLoopPatch_ASM,               7 ,   &fDefault},
	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FAE3883),    (DWORD)GameEndPatch_ASM,                5 ,   &fDefault},
	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB16EC5),    (DWORD)KeydownPatch_ASM,                7 ,   &fDefault},
	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB16DF1),    (DWORD)KeyupPatch_ASM,                  6 ,   &fDefault},
	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FAE1640),    (DWORD)MButtonDownPatch_ASM,            5 ,   &fDefault},
	

	{PatchVALUE,  DLLOFFSET(D2CLIENT, 0x6FACED38),    0xEB,									  1 ,   &fDefault}, //取消进出传送门时间限制

	{PatchCALL,   DLLOFFSET(D2WIN,    0x6F8F3D5F),    (DWORD)InstallPatchAfterLoad_ASM,       5 ,   &fDefault},

#endif

#ifdef PATH_INSTALL2
	//分一个给patch2占位置
	{PatchVALUE,  DLLOFFSET(D2CLIENT, 0x6FAC5D65),    0x3AEB,                                 2 ,   &fDefault}, //hover text bugfix,set old font

#endif

#ifdef CONFIG_LOAD

	{1, "ReloadConfigKey",			&tReloadConfig     },
	{2, "EnterGameSound",			&fEnterGameSound  ,   4 },
	{2, "ShowCFGCheckInfo",			&fShowCheckInfo  ,   4 },
	{3, "CFGVersionEng",			&szCFGVersion[0], 1,  {255 }},
	{3, "CFGVersionChi",			&szCFGVersion[1], 1,  {255 }},
	{2, "EnableLanguageCheck",		&fLanguageCheck  ,   4 },
	{2, "LocalizationSupport",      &fLocalizationSupport,  4},
	{2, "AutoSetCHISupport",        &fAutoSetCHISupport,  4},
	
#endif


#ifdef RUN_ONCE
	

	dwPlayerId = PLAYER->dwUnitId;
	if ( dwGameLng<0 ){
		if ( fLanguageCheck ){
			dwGameLng = GetGameLanguage();
			if (dwGameLng==2) {
				if ( fLocalizationSupport==1 && fAutoSetCHISupport){
					fLocalizationSupport = 2;
					wchar_t temp[512];
					GB2GBK(szCFGVersion[1]);
					MyMultiByteToWideChar(CP_ACP, 0, szCFGVersion[1], -1,temp , 0x200);
					wsprintfW(wszCFGVersion[1], L"<Hackmap>: %s " , temp);
				}
				dwGameLng = 1;
			}
		}else{
			dwGameLng = 0 ;
		}
	}
	
	InitCellFiles();

#endif

#ifdef RUN_ENDGAME
	DeleteCellFiles();
#endif

#ifdef RUN_LOOP
 
	
#endif

#ifdef INIT_VALUE
	memset( szCFGVersion ,    '\0' ,      sizeof(szCFGVersion) );
#endif

#ifdef FIX_VALUE
	
	if( szCFGVersion[0][0] ){
		wsprintfW2(wszCFGVersion[0], "<Hackmap>: %s " , szCFGVersion[0]);
	}

	if( szCFGVersion[1][0] ){
		wchar_t temp[512];
		if( fLocalizationSupport>1 ) GB2GBK(szCFGVersion[1]);
		MyMultiByteToWideChar(CP_ACP, 0, szCFGVersion[1], -1,temp , 0x200);
		wsprintfW(wszCFGVersion[1], L"<Hackmap>: %s " , temp);
	}else if( szCFGVersion[0][0] ){
		wsprintfW2(wszCFGVersion[1], "<Hackmap>: %s " , szCFGVersion[0]);
	}
	
	SetCenterAlertMsg(FALSE , L"");

#endif