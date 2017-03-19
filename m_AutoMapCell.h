#ifdef FUNCTION_DECLARE
#define MODULE_AUTOMAPCELL

void AddAutoMapCell(DrlgRoom2 *pRoom2);
void	OverrideShrinePatch_ASM();
void	AddShrinePatch_ASM();
void  __stdcall  DrawAutomapCellPatch(CellContext *pCellContext, DWORD xpos, DWORD ypos, RECT *cliprect, DWORD bright);
void RemoveMyAutomapCells();
#endif

#ifdef VARIABLE_DEFINE
GVAR2(ToggleVar,	tAutomapLevelNames,	    1,	0,	-1,		1, "Automap Level Names Toggle" )
GVAR2(ToggleVar,	tMiniShrine,			1,	0,	-1,		1, "Mini Shrine Toggle" )
GVAR (wchar_t,		wszStaffTombLvlDesc[50],      {L'\0'})
GVAR (BYTE,			nCaveNameTextCol,					0)
 
#endif

#ifdef PATH_INSTALL
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB01624),    (DWORD)OverrideShrinePatch_ASM,         7 ,   &fDefault},
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB02223),    (DWORD)AddShrinePatch_ASM,              6 ,   &fDefault},
  {PatchFILL,   DLLOFFSET(D2CLIENT, 0x6FB021D1),    INST_NOP,                               6 ,   &fDefault}, //shrine distance
  {PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FB006AA),    (DWORD)DrawAutomapCellPatch,            5 ,   &fDefault},
#endif

#ifdef CONFIG_LOAD
	{1, "AutomapLevelNamesToggle",  &tAutomapLevelNames		},
    {1, "MiniShrinesToggle",        &tMiniShrine			},
    {2, "LevelNameColour",          &nCaveNameTextCol , 1	},
	{4, "StaffTombLevelDesc",       &wszStaffTombLvlDesc, 1,  {50 }},

#endif


#ifdef RUN_ONCE
	

#endif

#ifdef RUN_LOOP


#endif

#ifdef RUN_ENDGAME
	

#endif

#ifdef INIT_VALUE
	memset( wszStaffTombLvlDesc ,      0 ,      sizeof(wszStaffTombLvlDesc) );

#endif

#ifdef FIX_VALUE
	if (nCaveNameTextCol>12)nCaveNameTextCol=0;

#endif