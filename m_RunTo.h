#ifdef FUNCTION_DECLARE
	void RunToSwitch();
	void RunToToggle();
	void RunTo( DWORD mode);
	void ClickPoint();
	void LButtonDownPatch_ASM();
	void __fastcall LButtonDownPatch();
	void __fastcall RButtonDownPatch();
	void RButtonDownPatch_ASM();
	void __fastcall LDownMouseMovingPatch();
	void LDownMouseMovingPatch_ASM();
	void __fastcall TestPatch();
	void TestPatch_ASM();
	void StartShake();
	void StopShake();
	void ShakeWhenMoving();
	
#endif


#ifdef VARIABLE_DEFINE

GVAR (DWORD,	    nRunTo,			 1) 
GVAR2(ToggleVar,	tRunToToggle,			2,	0,	-1,		1,	"Run To Toggle", &RunToToggle) 
GVAR2(ToggleVar,	tRunToSwitch,			2,	0,	-1,		1,	"Run To Switch",	&RunToSwitch)
//GVAR2(DWORD,			anRunPoints[100][100][10][4]	,{0})
//#define MOVINGVARIABLE   p_D2MovingVariable
//#define TESTVARIABLE   p_D2TestVariable
#endif

#ifndef RUNTO_H
#define RUNTO_H
extern bool doubleon;
//static long RelativePoints[100][2] ={
//	-53  , -204
//};
#endif

#ifdef PATH_INSTALL
	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FAD5ae0 ),    (DWORD)TestPatch_ASM,            5 ,   &fDefault},
	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FACFF60 ),    (DWORD)LDownMouseMovingPatch_ASM,            5 ,   &fDefault},
	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FAE2AA0 ),    (DWORD)LButtonDownPatch_ASM,            5 ,   &fDefault},
	{PatchCALL,   DLLOFFSET(D2CLIENT, 0x6FAE28F0 ),    (DWORD)RButtonDownPatch_ASM,            5 ,   &fDefault},
#endif

#ifdef CONFIG_LOAD

  
  {2, "RunTo", &nRunTo,     4 },
  {1, "RunToToggle",    &tRunToToggle   },
  {1, "RunToSwitch",    &tRunToSwitch   },
//  {5, "RunPoints",       &anRunPoints,       0, {100 , 100 , 10 }},

#endif


#ifdef RUN_ONCE
  

#endif

#ifdef RUN_LOOP


#endif


#ifdef INIT_VALUE
 
  //memset(anRunPoints,     -1,       sizeof(anRunPoints));
  //memset(RunPoints,     -1,       sizeof(RunPoints));
#endif

#ifdef FIX_VALUE


#endif
