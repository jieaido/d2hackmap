#ifndef D2_HELPFUNC_H
#define D2_HELPFUNC_H

void ShowGameMessage(char *Msg);
void ShowGameMessage(DWORD val);

CellFile *InitCellFile(CellFile *pCellFile);
void DeleteCellFile(CellFile *pCellFile);
CellFile *LoadBmpCellFile(char *filename);

DWORD GetTextWidth(wchar_t *wStr);
DWORD GetTextHeight(wchar_t *wStr);
void DrawAutomapCell(CellFile *pCellfile, int xpos, int ypos, BYTE col);

void DrawD2Text(DWORD dwFont, wchar_t *wStr, int xpos, int ypos, DWORD dwColor,DWORD dwAlign = 0);
void DrawCenterText(DWORD dwFont, wchar_t *wStr, int xpos, int ypos, DWORD dwColor, int div = 1 , DWORD dwAlign = 0 );
void DrawDefaultFontText(wchar_t *wStr, int xpos, int ypos, DWORD dwColor, int div = 1 , DWORD dwAlign = 0 );

void PreparePosForDraw(POINT* pos, int x, int y);
void MapToAbsScreen(POINT* pos, int x, int y);
WORD GetAreaLevel();
BYTE TestPvpFlag(DWORD dwUnitId , DWORD dwTargetUnitId);
int GetUnitResist(UnitAny *pUnit,DWORD dwStatNo);
BOOL TestMonsterOnScreen(UnitAny *mon, UnitAny *pla);
double __fastcall GetUnitDistanceInSubtiles(UnitAny *pUnit1 , UnitAny *pUnit2);
BOOL CheckUnitSelect( UnitAny *pUnit );
int GetItemAlvl(int Ilvl,int Qlvl,int magic_lvl);
int GetItemILvlAfterCube(int icubeType,int Ilvl , int Clvl);
void DrawCenterAlertMsg();
void SetCenterAlertMsg( BOOL draw ,wchar_t *wszMsg );
UnitAny * GetUnitPet(UnitAny *pUnit) ;
DWORD GetUnitMagicStat(UnitAny *pUnit , DWORD dwStatNo);
int GetGameLanguage();
void ExitGame();

void ScreenToAutomapRelative(POINT* pos, int x, int y);
void DrawCross(long newx , long newy , DWORD color ,int len);
void MouseScroll();
void DrawMousePointer();
void GetScrollDis(ScrollDis* scroll);
#endif