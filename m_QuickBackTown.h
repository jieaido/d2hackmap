#ifdef FUNCTION_DECLARE
	#define MODULE_QUICKBACKTOWN 
	void RecvCommand_60_Patch_ASM();

	


	void BackToTown();
	void OpenDoor();
	



#endif

#ifdef VARIABLE_DEFINE

 GVAR (BOOL,			fBackToTown,				FALSE)
 GVAR2(ToggleVar,		tBackToTown,		2,	0,	-1,		1,	0,		&BackToTown)
 GVAR (DWORD,			nTownportalAlertNums,			(DWORD)-1)
 GVAR2(ToggleVar,		tNoBackToTown,		1,	0,	-1,	1,  "No Back To Town Toggle")
  GVAR2(ToggleVar,		tOpenDoor,		2,	0,	-1,		1,	0,		&OpenDoor)
#endif

#ifdef PATH_INSTALL
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6E3F0),   (DWORD)RecvCommand_60_Patch_ASM,        5 ,   &fDefault},

/*
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6D960),   (DWORD)RecvCommand_6FB6D960_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6D9B0),   (DWORD)RecvCommand_6FB6D9B0_Patch_ASM,        5 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6DA00),   (DWORD)RecvCommand_6FB6DA00_Patch_ASM,        5 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6DA30),   (DWORD)RecvCommand_6FB6DA30_Patch_ASM,        5 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6DA50),   (DWORD)RecvCommand_6FB6DA50_Patch_ASM,        5 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6DAC0),   (DWORD)RecvCommand_6FB6DAC0_Patch_ASM,        5 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6DAF0),   (DWORD)RecvCommand_6FB6DAF0_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6DB20),   (DWORD)RecvCommand_6FB6DB20_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6DBA0),   (DWORD)RecvCommand_6FB6DBA0_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6DC20),   (DWORD)RecvCommand_6FB6DC20_Patch_ASM,        5 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6DCB0),   (DWORD)RecvCommand_6FB6DCB0_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6DD10),   (DWORD)RecvCommand_6FB6DD10_Patch_ASM,        5 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6DDE0),   (DWORD)RecvCommand_6FB6DDE0_Patch_ASM,        5 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6DE40),   (DWORD)RecvCommand_6FB6DE40_Patch_ASM,        5 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6DEC0),   (DWORD)RecvCommand_6FB6DEC0_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6DF70),   (DWORD)RecvCommand_6FB6DF70_Patch_ASM,        5 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6E200),   (DWORD)RecvCommand_6FB6E200_Patch_ASM,        5 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6E280),   (DWORD)RecvCommand_6FB6E280_Patch_ASM,        5 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6E2B0),   (DWORD)RecvCommand_6FB6E2B0_Patch_ASM,        5 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6E370),   (DWORD)RecvCommand_6FB6E370_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6E390),   (DWORD)RecvCommand_6FB6E390_Patch_ASM,        5 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6E440),   (DWORD)RecvCommand_6FB6E440_Patch_ASM,        5 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6E4A0),   (DWORD)RecvCommand_6FB6E4A0_Patch_ASM,        5 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6E520),   (DWORD)RecvCommand_6FB6E520_Patch_ASM,        5 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6E5F0),   (DWORD)RecvCommand_6FB6E5F0_Patch_ASM,        5 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6E770),   (DWORD)RecvCommand_6FB6E770_Patch_ASM,        5 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6E7A0),   (DWORD)RecvCommand_6FB6E7A0_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6E7E0),   (DWORD)RecvCommand_6FB6E7E0_Patch_ASM,        5 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6E840),   (DWORD)RecvCommand_6FB6E840_Patch_ASM,        5 ,   &fDefault},
{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6E960),   (DWORD)RecvCommand_6FB6E960_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6E980),   (DWORD)RecvCommand_6FB6E980_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6E9B0),   (DWORD)RecvCommand_6FB6E9B0_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6E9E0),   (DWORD)RecvCommand_6FB6E9E0_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6EA00),   (DWORD)RecvCommand_6FB6EA00_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6EA30),   (DWORD)RecvCommand_6FB6EA30_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6EA80),   (DWORD)RecvCommand_6FB6EA80_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6EAA0),   (DWORD)RecvCommand_6FB6EAA0_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6EAF0),   (DWORD)RecvCommand_6FB6EAF0_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6EB10),   (DWORD)RecvCommand_6FB6EB10_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6EB60),   (DWORD)RecvCommand_6FB6EB60_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6EBD0),   (DWORD)RecvCommand_6FB6EBD0_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6EC50),   (DWORD)RecvCommand_6FB6EC50_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6ED20),   (DWORD)RecvCommand_6FB6ED20_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6ED40),   (DWORD)RecvCommand_6FB6ED40_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6ED60),   (DWORD)RecvCommand_6FB6ED60_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6EE40),   (DWORD)RecvCommand_6FB6EE40_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6EED0),   (DWORD)RecvCommand_6FB6EED0_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6EF00),   (DWORD)RecvCommand_6FB6EF00_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6EF20),   (DWORD)RecvCommand_6FB6EF20_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6EF50),   (DWORD)RecvCommand_6FB6EF50_Patch_ASM,        5 ,   &fDefault},
//{PatchCALL,   DLLOFFSET(D2CLIENT , 0x6FB6EFB0),   (DWORD)RecvCommand_6FB6EFB0_Patch_ASM,        5 ,   &fDefault},
*/


#endif

#ifdef CONFIG_LOAD
	{1, "QuickBackToTownKey",   &tBackToTown		    	},
	{2, "TownportalNumsAlert",  &nTownportalAlertNums, 4    },
	{1, "NoBackToTownToggle",     &tNoBackToTown         },
	{1, "OpenDoorKey",   &tOpenDoor		    	},
#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP

	if( fPlayerInTown )fBackToTown = FALSE;

#endif


#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif