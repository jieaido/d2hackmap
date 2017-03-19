
#ifdef FUNCTION_DECLARE
	#define MODULE_PARTYHELP
	BOOL CheckInvite() ;
	void InviteAll() ;
	void PermitAll() ;
	void RecvCommand_5A_Patch_ASM();
	void RecvCommand_5B_Patch_ASM();
	void ResponseInvite();
#endif

#ifdef VARIABLE_DEFINE
GVAR (BOOL,			fCanInvite,			FALSE)
GVAR (BOOL,			fCanPermit,			FALSE)
GVAR2(ToggleVar,	tAutoParty,			1,	0,	-1, 1,	"Auto Party Toggle")
GVAR2(ToggleVar,	tAutoInvite,		1,	0,	-1,	1,  "Auto Invite Toggle")
GVAR2(ToggleVar,	tAutoPermit,		1,	0,	-1,	1,  "Auto Loot Permit Toggle")
GVAR (DWORD,		mAutoPartyDelays,			500)

#endif

#ifdef PATH_INSTALL

  {PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6E9B0),   (DWORD)RecvCommand_5A_Patch_ASM,        5 ,   &fDefault},
  {PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6EB70),   (DWORD)RecvCommand_5B_Patch_ASM,        6 ,   &fDefault},

#endif

#ifdef CONFIG_LOAD

  {1, "AutoPartyToggle",      &tAutoParty         },
  {1, "AutoInviteToggle",     &tAutoInvite        },
  {1, "AutoLootPermit",       &tAutoPermit        },
  {2, "AutoPartyDelays",      &mAutoPartyDelays, 4},

#endif


#ifdef RUN_ONCE
		if( CheckInvite() ){
			//由于数据包可能在进游戏前收到，所以需要强制邀请一次
			if ( tAutoInvite.isOn ) InviteAll();
			fCanInvite = TRUE;
		}

		if ( tAutoPermit.isOn ){
			PermitAll();
			fCanPermit = TRUE ;
		}

#endif

#ifdef RUN_LOOP
	
		ResponseInvite();



#endif


#ifdef RUN_ENDGAME

fCanInvite = FALSE;
fCanPermit = FALSE;

#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
