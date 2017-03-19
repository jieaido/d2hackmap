#ifdef FUNCTION_DECLARE
	#define MODULE_SCREENHOOK
	void InitScreenHook() ;
	void DrawClientPatch_ASM();
	void InitExp();
	void UpdateExp_ASM();
#endif

#ifdef VARIABLE_DEFINE
GVAR2(ToggleVar,	tShowExp,				1,	0,	-1,	  2,	"Show Exp Toggle"  )
GVAR2(ToggleVar,	tShowPing,				1,	0,	-1,	  1,	"Show Ping Toggle" )
GVAR(int , currentgameexp  ,0)
 
#endif

#ifdef PATH_INSTALL
 {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB16BA6),    (DWORD)DrawClientPatch_ASM,             5 ,   &fDefault},//无视系统菜单显示
 {PatchJMP,    DLLOFFSET(D2CLIENT, 0x6FB704B1),    (DWORD)UpdateExp_ASM,                   5 ,   &fDefault},// just got a update player state packet


#endif

#ifdef CONFIG_LOAD
	{1, "ShowExpToggle",	&tShowExp   },
	{1, "ShowPingToggle",	&tShowPing  }, 

#endif


#ifdef RUN_ONCE

	InitExp();
#endif

#ifdef RUN_LOOP


#endif


#ifdef RUN_ENDGAME


#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE

InitScreenHook();
#endif
