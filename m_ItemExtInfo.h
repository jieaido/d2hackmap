
#ifdef FUNCTION_DECLARE
	#define MODULE_ITEMEXTINFO
	void ShowItemExtInfo();
	void LoadExtInfo();
	void UnLoadExtInfo();
	void SetExtInfoPos(int xPos , int yPos , DWORD txtWidth , DWORD txtHeight);
	void DrawHoverPatch_ASM();
#endif

#ifdef VARIABLE_DEFINE

	GVAR2(char,			szItemExtInfoCfgName[2][256]	,			{'\0'})
	GVAR2(ToggleVar,	tItemExtInfo,			1,	0,	-1,	1 , 0 , &LoadExtInfo)
	GVAR (BYTE,			nDefaultExtInfoColour,				8)
#endif

#ifdef PATH_INSTALL
{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB16DA1),    (DWORD)DrawHoverPatch_ASM,             5 ,   &fDefault},//单独找个地方显示，保持独立

#endif

#ifdef CONFIG_LOAD

	{3, "ItemExtInfoFileEng",		&szItemExtInfoCfgName[0], 1,  {255 }},
	{3, "ItemExtInfoFileChi",		&szItemExtInfoCfgName[1], 1,  {255 }},
	{1, "ItemExtInfoToggle",		&tItemExtInfo         },
	{2, "DefaultExtInfoColour",     &nDefaultExtInfoColour,   1 },

#endif


#ifdef RUN_ONCE

	LoadExtInfo();
#endif

#ifdef RUN_LOOP


#endif


#ifdef RUN_ENDGAME


#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
