#ifdef FUNCTION_DECLARE
	#define MODULE_ROOMAREA
	void  RoomPatch_ASM();
	
#endif

#ifdef VARIABLE_DEFINE

GVAR2(ToggleVar,	tAutomapActiveRoom,		1,	0,	  -1	,1 )
GVAR2(ToggleVar,	tAutomapReadyRoom,		1,	0,	  -1	,1)
GVAR2(ToggleVar,	tAutomapScreenArea,		1,	0,	  -1	,1)
GVAR (BYTE,			nAutomapActiveRoomColors,	 0x16)
GVAR (BYTE,			nAutomapReadyColors,			7)
GVAR (BYTE,			nAutomapScreenColors,		 0x16)
 
#endif

#ifdef PATH_INSTALL
	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB010E6),    (DWORD)RoomPatch_ASM,                   6 ,   &fDefault},

#endif

#ifdef CONFIG_LOAD
  {1, "AutomapActiveRoomsToggle",		&tAutomapActiveRoom     },
  {1, "AutomapReadyRoomsToggle",		&tAutomapReadyRoom      },
  {1, "AutomapScreenAreaToggle",		&tAutomapScreenArea     },
  {2, "AutomapActiveRoomsColour",		&nAutomapActiveRoomColors,  1 },
  {2, "AutomapReadyRoomsColour",		&nAutomapReadyColors  , 1 },
  {2, "AutomapScreenAreaColour",		&nAutomapScreenColors , 1 },

#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP


#endif


#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif