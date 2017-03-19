#include "stdafx.h"

static wchar_t wszAlertMsg[512] = {L'\0'} ;
static BOOL blnDraw = FALSE;
void SetCenterAlertMsg( BOOL draw ,wchar_t *wszMsg ){	
	blnDraw = draw;
	if(blnDraw){
		wcscpy(wszAlertMsg,wszMsg);
	}
}
void DrawCenterAlertMsg(){
  //需要DrawClientPatch支持
	if(blnDraw){
		DrawCenterText(3, wszAlertMsg , SCREENSIZE.x/2, SCREENSIZE.y/2, 1, 1);
	}
}

void ShowGameMessage(char *Msg)
{
	wchar_t temp[512];
	wsprintfW2(temp, "<Hackmap>: %s ", Msg);
	D2ShowGameMessage(temp, 0);
}
void ShowGameMessage(DWORD val)
{
	wchar_t temp[512];
	wsprintfW(temp, L"<Hackmap>: %d ", val);
	D2ShowGameMessage(temp, 0);
}


WORD GetAreaLevel()
{	
	static DWORD dwLastLevelNo = 0 ;
	static WORD  wAreaLevel = 0 ;
	if( dwLastLevelNo != LEVELNO){
		dwLastLevelNo = LEVELNO;
		LevelTxt *pLvlTxt=D2GetLevelTxt(LEVELNO);
		wAreaLevel = pLvlTxt->nMonLv[EXPANSION][DIFFICULTY];	
	}
	return wAreaLevel;
} 

/*获得玩家的雇佣兵*/
UnitAny * GetUnitPet(UnitAny *pUnit) {
	PetUnit *pPetUnit = *p_D2PetUnitList;
	while(pPetUnit){
		if( pPetUnit->dwPetType==7 && pPetUnit->dwOwnerId == pUnit->dwUnitId && pPetUnit->dwOwerType==UNITNO_PLAYER ){
			return D2GetUnitFromId(pPetUnit->dwUnitId , UNITNO_MONSTER ) ;
		}
		pPetUnit = pPetUnit->pNext ;
	}
	return NULL;
}



BYTE TestPvpFlag(DWORD dwUnitId , DWORD dwTargetUnitId){
	// 0 敌对  1 中立 2 队友 3 自身
	if (dwUnitId==dwTargetUnitId) return 3;
	WORD wPartyId = (WORD)-1 , wPartyIdTarget = (WORD)-1 ;
	for (RosterUnit *pUnit = PLAYERLIST ; pUnit; pUnit=pUnit->pNext){
		if ( pUnit->dwUnitId== dwUnitId){
			wPartyId=pUnit->wPartyId;
			if ( pUnit->pPvPInfo ){
				PvPInfo *pPvPInfo =  *(pUnit->pPvPInfo);
				while( pPvPInfo ){
					if (pPvPInfo->dwUnitId==dwTargetUnitId){
						if (pPvPInfo->dwFlag & 8){
							return 0 ;
						}else{
							break;	
						}
					}
					pPvPInfo = pPvPInfo->pNext;
				}
			}
		}else if ( pUnit->dwUnitId==dwTargetUnitId){
			wPartyIdTarget=pUnit->wPartyId;
			if( wPartyId!=(WORD)-1 )break;
		}
	}
	if( wPartyId!=(WORD)-1 && wPartyId==wPartyIdTarget)return 2;
	return 1 ;
}

//获取玩家距离，单位码数
double __fastcall GetUnitDistanceInSubtiles(UnitAny *pUnit1 , UnitAny *pUnit2){

	DWORD xpos1 ,xpos2 , ypos1 , ypos2 ;
	if ( pUnit1->dwUnitType==UNITNO_PLAYER || pUnit1->dwUnitType==UNITNO_MONSTER || pUnit1->dwUnitType==UNITNO_MISSILE){
		xpos1 = D2GetUnitPosX(pUnit1->pMonPath);
		ypos1 = D2GetUnitPosY(pUnit1->pMonPath);
	}else{
		xpos1 = pUnit1->pItemPath->dwPosX;
		ypos1 = pUnit1->pItemPath->dwPosY;
	}
	if ( pUnit2->dwUnitType==UNITNO_PLAYER || pUnit2->dwUnitType==UNITNO_MONSTER || pUnit2->dwUnitType==UNITNO_MISSILE){
		xpos2 = D2GetUnitPosX(pUnit2->pMonPath); 
		ypos2 = D2GetUnitPosY(pUnit2->pMonPath); 
	}else{
		xpos2 = pUnit2->pItemPath->dwPosX;
		ypos2 = pUnit2->pItemPath->dwPosY;
	}
	
	return 2*sqrt( double((xpos1-xpos2)*(xpos1-xpos2) + (ypos1-ypos2)*(ypos1-ypos2)))/3;
}

//获得魔法属性,只查询第一层
DWORD GetUnitMagicStat(UnitAny *pUnit , DWORD dwStatNo) {
	StatList *pStatList = D2GetStatListWithFlag( pUnit,	0,	0x40 );
	StatEx stat ;
	if ( pStatList && D2GetStatFromStatList(pStatList,dwStatNo , &stat , 0x1ff) ) return stat.dwStatValue;
	return 0;
}





//抗性惩罚

int GetUnitResist( UnitAny *pUnit , DWORD dwStatNo )
{
	static int resistoffset[2][3]={{0,-20,-50},{0,-40,-100}};

	int resist = D2GetUnitStat(pUnit, dwStatNo, 0) + resistoffset[EXPANSION][DIFFICULTY];
	if ( resist<-100 ) resist = -100 ;

	return resist;
}

//目标是否能选择(有装备)
BOOL CheckUnitSelect( UnitAny *pUnit ){
	if ( pUnit && pUnit->pInventory ){
		if ( pUnit->dwUnitType == UNITNO_PLAYER ){
			return pUnit->dwMode && pUnit->dwMode != 0x11;
		}
		if ( pUnit->dwUnitType == UNITNO_MONSTER ){

			if ( pUnit->dwMode && pUnit->dwMode != 0x0C ) {

				switch ( pUnit->dwTxtFileNo ){
					case 357:
					case 291:
					case 417:
					case 418:
						return TRUE ;
					default:
						return  FALSE;
				}

			}

		}
	}
	return FALSE;
}

int GetItemILvlAfterCube(int icubeType,int Ilvl , int Clvl)
{
	int NewLvl;
	if(icubeType==1)//craft
	{
		NewLvl=(Ilvl>>1)+(Clvl>>1);
		return NewLvl>99?99:(NewLvl<1?1:NewLvl);
	}
	else if(icubeType==2)//skull cube
	{
		NewLvl=(int)(Ilvl*0.4)+(int)(Clvl*0.4);
		return NewLvl>99?99:(NewLvl<1?1:NewLvl);
	}
	return 0;
}
int GetItemAlvl(int Ilvl,int Qlvl,int magic_lvl)
{
	int Alvl;
	if (Ilvl>99) Ilvl=99 ;
	if (Qlvl>Ilvl) Ilvl=Qlvl;
	if (magic_lvl>0) 
		Alvl=Ilvl+magic_lvl;
	else
	{
		if ( Ilvl<( 99-(Qlvl>>1) ) )
			Alvl=Ilvl-(Qlvl>>1) ;
		else 
			Alvl=(Ilvl<<1)-99;
	}
	return Alvl>99?99:Alvl;
}


//是否屏幕中
BOOL TestMonsterOnScreen(UnitAny *mon, UnitAny *pla)
{
	return abs((int)mon->pMonPath->dwMapPosX-(int)pla->pMonPath->dwMapPosX) < SCREENSIZE.x/2
		&& abs((int)mon->pMonPath->dwMapPosY-(int)pla->pMonPath->dwMapPosY) < (SCREENSIZE.y-48)/2;
}
void PreparePosForDraw(POINT* pos, int x, int y)
{
	pos->x = x/DIVISOR-OFFSET.x+8;
	pos->y = y/DIVISOR-OFFSET.y-8;
	if ( MINMAPTYPE ) {
		--pos->x;
		pos->y += 5;
	}
}

void MapToAbsScreen(POINT* pos, int x, int y)
{
	pos->x = 5*(x-y)*16;
	pos->y = 5*(x+y)*8;
}



CellFile *LoadBmpCellFile(BYTE *buf1, int width, int height)
{
	BYTE *buf2 = new BYTE[(width*height*2)+height], *dest = buf2;

	for (int i = 0; i < height; i++) {
		BYTE *src = buf1+(i*((width+3)&-4)), *limit = src+width;
		while (src < limit) {
			BYTE *start = src, *limit2 = min(limit, src+0x7f), trans = !*src;
			do src++; while ((trans == (BYTE)!*src) && (src < limit2));
			if (!trans || (src < limit)) *dest++ = (trans?0x80:0)+(src-start);
			if (!trans) while (start < src) *dest++ = *start++;
		}
		*dest++ = 0x80;
	}

	static DWORD dc6head[] = {6, 1, 0, 0xeeeeeeee, 1, 1, 0x1c,  0, -1, -1, 0, 0, 0, -1, -1};
	dc6head[8] = width;
	dc6head[9] = height;
	BYTE *ret = new BYTE[dc6head[13] = sizeof(dc6head)+(dc6head[14] = dest-buf2)+3];
	memset(memcpy2(memcpy2(ret, dc6head, sizeof(dc6head)), buf2, dc6head[14]), 0xee, 3);
	delete buf2;

	return (CellFile *)ret;
}

CellFile *LoadBmpCellFile(char *filename)
{
	BYTE *ret = 0;
		
	BYTE *buf1 = AllocReadFile(filename);
	BITMAPFILEHEADER *bmphead1 = (BITMAPFILEHEADER *)buf1;
	BITMAPINFOHEADER *bmphead2 = (BITMAPINFOHEADER *)(buf1+sizeof(BITMAPFILEHEADER));
	if (buf1 && (bmphead1->bfType == 'MB') && (bmphead2->biBitCount == 8) && (bmphead2->biCompression == BI_RGB)) {
		ret = (BYTE *)LoadBmpCellFile(buf1+bmphead1->bfOffBits, bmphead2->biWidth, bmphead2->biHeight);
	}
	delete buf1;

	return (CellFile *)ret;
}

CellFile *InitCellFile(CellFile *pCellFile)
{
	if (pCellFile) D2InitCellFile(pCellFile, &pCellFile, "?", 0, -1, "?");
	return pCellFile;
}

void DeleteCellFile(CellFile *pCellFile)
{
	if (pCellFile) {
		D2DeleteCellFile(pCellFile);
		delete pCellFile;
	}
}

DWORD GetTextHeight(wchar_t *wStr)
{
	DWORD dwWidth, dwHeight;
	D2GetTextAreaSize(wStr, &dwWidth, &dwHeight);
	return dwHeight;
}

DWORD GetTextWidth(wchar_t *wStr)
{
	DWORD dwWidth, dwHeight;
	D2GetTextAreaSize(wStr, &dwWidth, &dwHeight);
	return dwWidth;
}


void DrawD2Text(DWORD dwFont, wchar_t *wStr, int xpos, int ypos, DWORD dwColor,DWORD dwAlign)
{
	DWORD dwOldFone = D2SetTextFont(dwFont);
	D2DrawText(wStr, xpos, ypos, dwColor, dwAlign);
	D2SetTextFont(dwOldFone);
}

void DrawCenterText(DWORD dwFont, wchar_t *wStr, int xpos, int ypos, DWORD dwColor, int div , DWORD dwAlign)
{
	DWORD dwOldFone = D2SetTextFont(dwFont);
	D2DrawText(wStr, xpos-(GetTextWidth(wStr)>>div), ypos, dwColor, dwAlign);//dwAlign:多行时对齐有用 1居中 0 靠左
	D2SetTextFont(dwOldFone);
}

void DrawDefaultFontText(wchar_t *wStr, int xpos, int ypos, DWORD dwColor, int div , DWORD dwAlign)
{
	D2DrawText(wStr, xpos-(D2GetTextPixelLen(wStr)>>div), ypos, dwColor, dwAlign);//dwAlign:多行时对齐有用 1居中 0 靠左
}


void ExitGame()
{
	*p_D2ExitAppFlag = 0;
	SendMessage(D2GetHwnd(), WM_CLOSE, 0, 0);
}


void DrawAutomapCell(CellFile *pCellfile, int xpos, int ypos, BYTE col)
{
	if ( !pCellfile )return ;
	
	CellContext ct;
	memset(&ct, 0, sizeof(ct));
	ct.pCellFile = pCellfile ;

	xpos -= (pCellfile->pCells[0]->dwWidth/2);
	ypos += (pCellfile->pCells[0]->dwHeight/2);

	int xpos2 = xpos - pCellfile->pCells[0]->dwXoffs ;
	int ypos2 = ypos - pCellfile->pCells[0]->dwYoffs ;

	if ( ( xpos2 >= SCREENSIZE.x ) || ( (xpos2 + (int)pCellfile->pCells[0]->dwWidth) <= 0 ) || (ypos2 >= SCREENSIZE.y) || ((ypos2 + (int)pCellfile->pCells[0]->dwHeight) <= 0) ) return;

	static BYTE coltab[2][256];//, tabno = 0, lastcol = 0;
	if (!coltab[0][1]) for (int k = 0; k < 255; k++) coltab[0][k] = coltab[1][k] = k;
	pCellfile->mylastcol = coltab[pCellfile->mytabno ^= (col != pCellfile->mylastcol)][255] = col;

	D2DrawCellFile(&ct, xpos, ypos, -1, 5, coltab[pCellfile->mytabno]);
}


int GetGameLanguage(){

	wchar_t wszTemp[512];
	wcscpy(wszTemp,D2GetLocaleText(0xFDA));
	if( wszTemp[0] == L'E'){
		return 0;
	}else{
		if ( wszTemp[0] == 32147 ){
			return 2;
		}
		return 1;
	}

}