
#ifdef FUNCTION_DECLARE
	#define MODULE_MONSTERDEATH
	void MonsterDeathPatch_ASM();
#endif

#ifdef VARIABLE_DEFINE
GVAR2(BYTE,			afMonsterDeathAnims[1000]	,   {0})
 
#endif

#ifdef PATH_INSTALL
{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB3279E),    (DWORD)MonsterDeathPatch_ASM,           5 ,   &fDefault},

#endif

#ifdef CONFIG_LOAD

{5, "MonsterDeathAnims",      &afMonsterDeathAnims, 1,{1000}},
#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP


#endif


#ifdef RUN_ENDGAME


#endif

#ifdef INIT_VALUE
	memset(afMonsterDeathAnims,   1 ,     sizeof(afMonsterDeathAnims));

#endif

#ifdef FIX_VALUE


#endif
