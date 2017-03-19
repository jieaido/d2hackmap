#include "stdafx.h"

#ifdef MODULE_VIEWUNITSTAT

static const int PAGESHOWNUMS = 7;
static int nCurrentPage = 0 ; 

void SwitchStatPage(int nStep){
	if ( nStep == 0 ){
		nCurrentPage = 0 ;
	}else{
		nCurrentPage = nCurrentPage + nStep ;
	}
	if( nCurrentPage<0 )nCurrentPage = 2;
	if( nCurrentPage>2 )nCurrentPage = 0;

}

void DrawUnitStat(int align , int unitstat, int xpos, int ypos, char *szFormat ,char* szSuffix, char* szDesc, DWORD dwColor=0 , int desclen =0, int vallen=0)
{
	wchar_t wszTemp[256];
	xpos = xpos + DRAWOFFSET.x;
	ypos = ypos - DRAWOFFSET.y;

	if (*szDesc){

		wsprintfW2(wszTemp, "%s", szDesc);
		D2DrawText(wszTemp, xpos, ypos, dwColor, 0);
		xpos += desclen ;

		D2DrawText(L":", xpos, ypos, dwColor, 0);
		xpos += vallen;

	}
	wsprintfW2(wszTemp, szFormat ,unitstat,szSuffix);
	DrawDefaultFontText(wszTemp,	xpos ,	ypos ,	dwColor , align);
}

void __fastcall ViewUnitStatPatch(UnitAny *pUnit){
	
	/*
		这几个固定位置显示
		{STAT_MAGIC_FIND,			"MF" ,	"%"},
		{STAT_EXTRA_GOLD,			"EG" ,	"%"},
		{STAT_PLR,					"PLR",	 ""},
		{STAT_DAMAGE_REDUCED,		"DR" ,	"%"},
	*/

	static PlayerStat aPlayerStats[] = {
		{STAT_HPREGEN,				"REP" ,	" "},	
		{STAT_FCR,					"FCR" , "%"},
		{STAT_FHR,					"FHR" , "%"},
		{STAT_FRW,					"FRW" , "%"},
		{STAT_IAS,					"IAS" , "%"},
		{STAT_CB,					"CB" ,	"%"},
		{STAT_OW,					"OW" ,	"%"},

		{STAT_FBR,					"FBR" , "%"},
		{STAT_DS,					"DS" ,	"%"},
		{STAT_LIFE_LEECH,			"LL" ,	"%"},
		{STAT_MANA_LEECH,			"LM" ,	"%"},
		{STAT_DTM,					"DTM",	"%"},
		{STAT_MAGIC_DAMAGE_REDUCED, "MDR",	" "},
		{STAT_EK,					"EK",	" "},

		{STAT_FIRE_ABSORB,			"FA" ,	"%"},
		{STAT_LIGHTING_ABSORB,		"LA" ,	"%"},
		{STAT_COLD_ABSORB,			"CA" ,	"%"}
	}; // size 17 ;
	
	DWORD dwOldFone = D2SetTextFont(1);

	BOOL blStatButton = D2GetUnitStat(pUnit, STAT_STATPOINTSLEFT, 0);

	int xPos = 20 ;
	int yPos = blStatButton ? 330:345 ;
	char *szFormat = "%3d%s";
	for( int i = nCurrentPage*PAGESHOWNUMS,j=0 ; i< _ARRAYSIZE(aPlayerStats) && j<PAGESHOWNUMS ; i++,j++ ){

		if( j==2 && blStatButton ) yPos+=25;
		int unitstat = D2GetUnitStat(pUnit, aPlayerStats[i].dwStatNo, 0) ;
		DrawUnitStat(0, unitstat , xPos, yPos+j*13 ,szFormat , aPlayerStats[i].szSuffix , aPlayerStats[i].szDesc , 0 , 33 , 45 );

	}
	DrawUnitStat(0, D2GetUnitStat(pUnit, STAT_MAGIC_FIND, 0)  ,	 xPos,	196 , "%4d%s" , "%" , "MF" , 2 , 25 , 54 );
	DrawUnitStat(0, D2GetUnitStat(pUnit, STAT_EXTRA_GOLD, 0)  ,	 xPos,	213 , "%4d%s" , "%" , "EG" , 4 , 25 , 54 );

	DrawUnitStat(1, D2GetUnitStat(pUnit, STAT_DAMAGE_REDUCED, 0) , 175,	330 , "%d%s" , "%" , "DR" , 0 , 25 , 25 );
	DrawUnitStat(0, D2GetUnitStat(pUnit, STAT_PLR, 0)  ,		   250,	330 , "%d"	 ,  "" , "PLR", 0 , 30 , 30 );

	xPos = 187;
	yPos = 350;
	
	DrawUnitStat(1, GetUnitResist(pUnit,STAT_FIRE_RESIST),    xPos,	yPos,      "%d" , "" ,"", 1);
	DrawUnitStat(1, GetUnitResist(pUnit,STAT_COLD_RESIST),    xPos,	yPos+23,   "%d" , "" ,"", 3);
	DrawUnitStat(1, GetUnitResist(pUnit,STAT_LIGHTING_RESIST),xPos,	yPos+23*2, "%d" , "" ,"", 9);
	DrawUnitStat(1, GetUnitResist(pUnit,STAT_POSION_RESIST),  xPos,	yPos+23*3, "%d" , "" ,"",12);
 
	if ( tShowBaseStat.isOn ){

		xPos = blStatButton ? 95 : 140 ;
		yPos = blStatButton ? 118 : 100 ;
		DrawUnitStat(1, D2GetUnitBaseStat( pUnit,STAT_STRENGTH ,  0 ),    xPos,	yPos, "[%d]" , "" ,"");
		//+62
		yPos = yPos + 62 ;
		DrawUnitStat(1, D2GetUnitBaseStat( pUnit,STAT_DEXTERITY , 0 ),    xPos,	yPos, "[%d]" , "" ,"");
		//+85
		yPos = yPos + 85 ;
		DrawUnitStat(1, D2GetUnitBaseStat( pUnit,STAT_VITALITY ,  0 ),    xPos,	yPos, "[%d]" , "" ,"");
		
		//+25  +63
		yPos = yPos + (blStatButton? 25 : 63) ;
		DrawUnitStat(1, D2GetUnitBaseStat( pUnit,STAT_ENERGY ,    0 ),    xPos,	yPos, "[%d]" , "" ,"");

	}
	
	D2SetTextFont(dwOldFone);
}

void __declspec(naked) ViewUnitStatPatch_ASM()
{
	//esp+1C  pUnit
	__asm {
		mov ecx, [esp+0x1C]
		call ViewUnitStatPatch
//org
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 0x370
		ret
	}
}

void __fastcall ViewPetStatPatch(UnitAny *pUnit){

	int xPos = 10 ;
	int yPos = 395 ;
	DWORD dwColor = 0 ;

	DWORD dwOldFone = D2SetTextFont(1);

	DrawUnitStat(0, D2GetUnitStat(pUnit, STAT_MAGIC_FIND, 0)  ,	 xPos,	yPos ,    "%3d%s" , "%" , "MF" , 2 , 22 , 43 );
	DrawUnitStat(0, D2GetUnitStat(pUnit, STAT_EXTRA_GOLD, 0)  ,	 xPos,	yPos+15 , "%3d%s" , "%" , "EG" , 4 , 22 , 43 );
	DrawUnitStat(0, D2GetUnitStat(pUnit, STAT_DAMAGE_REDUCED, 0), xPos,	yPos+30 , "%3d%s" , "%" , "DR" ,  dwColor , 22 , 43 );

	xPos = xPos + 95 ; 
	dwColor = 0 ;
	DrawUnitStat(0, D2GetUnitStat(pUnit, STAT_FHR, 0)  ,	 xPos,	yPos ,    "%2d%s" , "%" , "FHR" , dwColor , 26 , 39 );
	DrawUnitStat(0, D2GetUnitStat(pUnit, STAT_IAS, 0)  ,	 xPos,	yPos+15 , "%2d%s" , "%" , "IAS" , dwColor , 26 , 39 );
	DrawUnitStat(0, D2GetUnitStat(pUnit, STAT_CB, 0)   ,	 xPos,	yPos+30 , "%2d%s" , "%" , "CB" ,  dwColor , 26 , 39 );
	
	xPos = xPos + 90 ; 
	dwColor = 0 ;
	DrawUnitStat(0, D2GetUnitStat(pUnit, STAT_DS, 0)  ,	 xPos,	yPos ,    "%2d%s" , "%" , "DS" , dwColor , 25 , 39 );
	DrawUnitStat(0, D2GetUnitStat(pUnit, STAT_OW, 0)  ,	 xPos,	yPos+15 , "%2d%s" , "%" , "OW" , dwColor , 25 , 39 );
	DrawUnitStat(0, D2GetUnitStat(pUnit, STAT_LIFE_LEECH, 0),xPos,	yPos+30 , "%2d%s" , "%" , "LL" ,  dwColor , 25 , 39 );
	
	D2SetTextFont(dwOldFone);

}
void __declspec(naked) ViewPetStatPatch_ASM()
{
	//ebx = pUnit
	__asm {
		push ecx
		push ebx
		mov ecx , ebx
		call ViewPetStatPatch;
		pop ebx
		pop ecx
		add ecx, 0x00000110
		ret;
	}
}




#endif