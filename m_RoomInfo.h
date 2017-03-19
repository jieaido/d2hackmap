#ifdef FUNCTION_DECLARE
	#define MODULE_ROOMINFO
	void SetTickCount();
	void __fastcall DrawGameInfoPatch(DWORD dwFont) ;
	void FixBodyImageOffset_ASM();
#endif

#ifdef VARIABLE_DEFINE

	GVAR2(ToggleVar,	tServerIp,			    1,	1,	-1,		1,	"Server Ip" )
	GVAR2(ToggleVar,	tGameTime,				1,	1,	-1,		1,	"Game Time" )
	GVAR2(ToggleVar,	tClock,					1,	1,	-1,		1,	"Clock" )
	GVAR2(ToggleVar,	tLayerLevelNo,			1,	0,	-1,		1,	"Layer LevelNo" )
	GVAR2(ToggleVar,	tAreaLevel,				1,	0,	-1,		1,	"Area Level" )
	GVAR (DWORD,		mYposOffset,			0)
 
#endif

#ifdef PATH_INSTALL

	{PatchJMP,    DLLOFFSET(D2CLIENT, 0x6FB02B9E),    (DWORD)DrawGameInfoPatch,               5 ,   &fDefault},//游戏右上角信息显示
	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB66B8F),    (DWORD)FixBodyImageOffset_ASM,		  6 ,   &fDefault},//画人物全身像偏移赋值
#endif

#ifdef CONFIG_LOAD
  {1, "ServerIpToggle",			&tServerIp        },
  {1, "GameTimeToggle",         &tGameTime        },
  {1, "ClockToggle",            &tClock           },
  {1, "LayerLevelNoToggle",     &tLayerLevelNo    },
  {1, "AreaLevelToggle",        &tAreaLevel       },

#endif


#ifdef RUN_ONCE
	SetTickCount();

#endif

#ifdef RUN_LOOP


#endif


#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif