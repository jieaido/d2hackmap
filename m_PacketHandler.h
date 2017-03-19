#ifdef FUNCTION_DECLARE
	#define MODULE_PACKETHANDLER
	void GamePacketReceivedInterceptPatch_ASM();
#endif

#ifdef VARIABLE_DEFINE

 GVAR2(ToggleVar,	tPacketHandler,				1,	0,	-1,	1,  0 )
#endif

#ifdef PATH_INSTALL
//{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB6DFCF),      (DWORD)GamePacketReceivedInterceptPatch_ASM, 6 , &fDefault},
//TODO 测试发送包前
//测试地址 
// 0x6FB6DF70
// 0x6FAE2050
// 0x6FAE3290
// 0x6FB0D410
// 0x6FB6E0FA
// 0x6FB6DFA6

//{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FAD1250),      (DWORD)GamePacketReceivedInterceptPatch_ASM, 6 , &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FABE1C0),      (DWORD)GamePacketReceivedInterceptPatch_ASM, 6 , &fDefault},


//6FAC2D70
//6FAC3790
//6FAC3940
//{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FAC3940),      (DWORD)GamePacketReceivedInterceptPatch_ASM, 6 , &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FABE1C0),      (DWORD)GamePacketReceivedInterceptPatch_ASM, 6 , &fDefault},

//{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FABE1C0),      (DWORD)GamePacketReceivedInterceptPatch_ASM, 6 , &fDefault},

//{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FABE1C0),      (DWORD)GamePacketReceivedInterceptPatch_ASM, 6 , &fDefault},

//{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FABE1C0),      (DWORD)GamePacketReceivedInterceptPatch_ASM, 6 , &fDefault},

//{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FABE1C0),      (DWORD)GamePacketReceivedInterceptPatch_ASM, 6 , &fDefault},

#endif

#ifdef CONFIG_LOAD
{1, "PacketHandlerToggle",          &tPacketHandler         },

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
