#include "stdafx.h"
#ifdef MODULE_AUTOMAPCELL

void RemoveAutomapCell( AutomapCell *pCell )
{
	if ( pCell ){
		RemoveAutomapCell ( pCell->pLess );
		if (pCell->wCellNo >= CELLNO_MYSHRINES && pCell->wCellNo < CELLNO_MYSHRINES+23) {
			pCell->wCellNo = CELLNO_SHRINE;
		} else if ((short)pCell->wCellNo < 0) {
			pCell->wCellNo = 0;
		}
		RemoveAutomapCell ( pCell->pMore );
	}
}

void RemoveMyAutomapCells()
{	
	DWORD curLayer = LAYER->dwLayerNo;
	for (AutomapLayer *pAutomapLayer = LAYERLIST; pAutomapLayer != NULL; pAutomapLayer = pAutomapLayer->pNext) {
		D2InitAutomapLayer(pAutomapLayer->dwLayerNo);
		RemoveAutomapCell( pAutomapLayer->pObjects );
	}
	D2InitAutomapLayer(curLayer);
}


void AddAutoMapCell(DrlgRoom2 *pRoom2){

	PresetUnit *pUnit = pRoom2->pPresetUnits;
	while (pUnit) {
		BOOL fAddCell = FALSE ; //是否新增加小地图图标
		BOOL fAddMinimap = FALSE ; //是否增加到待指示列表

		int cellno = 0, xpos = 0, ypos = 0 , xoffset = 0 , yoffset = 0 ;
		switch ( pUnit->dwUnitType ) {
			case UNITNO_MONSTER:
				{
					if (pUnit->dwTxtFileNo == 256){		//izual
						cellno = 300; 
						fAddCell = TRUE;
						fAddMinimap = TRUE;
					}
				}
				break;
			case UNITNO_OBJECT:
				{
					fAddCell = TRUE;
					fAddMinimap = TRUE;
					DWORD levelno = pRoom2->pDrlgLevel->dwLevelNo;
					switch( pUnit->dwTxtFileNo ){
						case 397 ://chests
							cellno = 318 ;
							fAddMinimap = FALSE;
							break;
						case 371 ://countess chest
							cellno = 1472 ;
							fAddCell = FALSE;
							break;
						case 152 ://orifice
							cellno = 300 ;
							break;
						case 460 ://drehya = frozen anya
							cellno = 1468 ;
							break;
						case 462 ://nihlathak
							cellno = 1472 ;
							fAddCell = FALSE;
							break;
						case 376 :// hell forge
							cellno = 376 ;
							fAddCell = FALSE;
							break;
						case 402 ://canyon/arcane waypoint
							if( levelno == 46 ){
								cellno = 0 ;
								break;
							}
						case 267 ://chests
							if( levelno != 75 &&  levelno != 103){
								cellno = 0 ;
								break;
							}
						default :
							{
								if ( pUnit->dwTxtFileNo>= 573){
									cellno = 0 ;
								}else{
									ObjectTxt *pObj = D2GetObjectTxt(pUnit->dwTxtFileNo);
									cellno = pObj->nAutoMap;
									
									if (cellno == CELLNO_SHRINE) {//配合AddShrinePatch_ASM
										static WORD parm0cells[4] = {
											CELLNO_MYSHRINES+0, //0 = ??
											CELLNO_MYSHRINES+2, //1 = health
											CELLNO_MYSHRINES+3, //2 = mana
											CELLNO_MYSHRINES+0, //3 = magic
										};
										cellno = (pObj->nSubClass & 1) ? parm0cells[ pObj->dwParm[0] ] : 0;
										fAddMinimap = FALSE;
									}
								}
							}
							break;
					}
					
				}

				break;
			case UNITNO_ROOMTILE:
				{
					for(RoomTile *pRoomtile = pRoom2->pRoomTiles ;pRoomtile ; pRoomtile = pRoomtile->pNext ){
						if ( *(pRoomtile->pNum)==pUnit->dwTxtFileNo){
							cellno = -(int)(pRoomtile->pRoom2->pDrlgLevel->dwLevelNo);
							xoffset = +8;	//change pos here because better for minimap
							yoffset = -28;
							fAddCell = TRUE;
							fAddMinimap = TRUE;
						}
					}
				}
				break;
		}

		if( cellno ){
			xpos = ( pRoom2->dwPosX*5 ) + pUnit->dwPosX ;
			ypos = ( pRoom2->dwPosY*5 ) + pUnit->dwPosY ;

			//相当于调用D2COMMON_MapToAbsScreen后 /DIVISOR 固定10以防止大小地图切换引起地址不同
			int xpos1 = ((xpos-ypos)*16)/10 +1;
			int ypos1 = ((xpos+ypos)*8)/10 -3;

			if ( fAddCell==TRUE ){//需要结合DrawAutomapCellPatch
				AutomapCell *pCell = D2NewAutomapCell();
				pCell->wCellNo = (WORD)cellno;
				pCell->xPixel = (WORD)(xpos1+xoffset);
				pCell->yPixel = (WORD)(ypos1+yoffset);
				D2AddAutomapCell(pCell, &LAYER->pObjects);
			}
			
			#ifdef MODULE_MINIMAPPOINT
				if( fAddMinimap==TRUE ) {
					AddMinimapCell( pRoom2->pDrlgLevel , cellno , xpos1-1,  ypos1+3 );
				}
			#endif
			
		}

		pUnit = pUnit->pNext;
	}

}

	
void __stdcall DrawAutomapCellPatch(CellContext *pCellContext, DWORD xpos, DWORD ypos, RECT *cliprect, DWORD bright)
{
	int cellno = pCellContext->dwCellNo;

	if (cellno < 0) {
		if (tAutomapLevelNames.isOn) { 
			wchar_t temp[1024];
			wcscpy ( temp, D2GetLevelTxt(-cellno)->wszName ) ;
			if ( wszStaffTombLvlDesc[0] && (-cellno == (int)ACT->pDrlgMisc->dwStaffTombLvl) ){
				wscolorcpy(temp+wcslen(temp), wszStaffTombLvlDesc ,nCaveNameTextCol);
			}
			if ( -cellno == (int)ACT->pDrlgMisc->dwBossTombLvl ){
				wchar_t temp2[25] = L"<==UniqueBoss Here" ;
				wcscat(temp , temp2 );
			}
			DrawCenterText( 6, temp, xpos, ypos, nCaveNameTextCol);
		}
		return;
	}
	if (cellno == CELLNO_WAYPOINT && pWaypointCell != 0)
	{
		pCellContext->dwCellNo = 0;
		pCellContext->pCellFile = pWaypointCell;
		xpos += (MINMAPTYPE ? 4 : 8)-(pWaypointCell->pCells[0]->dwWidth/2);
		ypos += (MINMAPTYPE ? 4 : 0);
	}

	if ( ( (cellno -= CELLNO_MYSHRINES) >= 0 ) && (cellno < NUMOF_SHRINES) ) {
		CellFile *pMyShrine = apMyShrineCells[ MINMAPTYPE ][cellno];
		if ( pMyShrine && tMiniShrine.isOn ) {
			pCellContext->pCellFile = pMyShrine;
			pCellContext->dwCellNo = 0;
			xpos += (MINMAPTYPE ? 4 : 8)-(pMyShrine->pCells[0]->dwWidth/2);
		} else {
			pCellContext->dwCellNo = CELLNO_SHRINE;
		}
	}

	D2DrawAutomapCell(pCellContext, xpos, ypos, cliprect, bright);

}

void __declspec(naked) AddShrinePatch_ASM()
{
	__asm {

// 1.11-1.13
//ebx = ptr unit object
//esi = ptr object.txt
//return ecx = cell no

//		mov ecx,[esi]ObjectTxt.nAutoMap //original code
		mov ecx,[esi+0x1BC]
		cmp ecx,CELLNO_SHRINE
		jne notshrine
		xor ecx,ecx
//		test [esi]ObjectTxt.nSubClass,1
		test [esi+0x167],1
		je notshrine
//		mov eax,[ebx]UnitAny.pObjectData
		mov eax,[ebx+0x14]
//		movzx ecx,[eax+0x04]ObjectData.nShrineNo
		movzx ecx,byte ptr [eax+0x04]
		add ecx,CELLNO_MYSHRINES
notshrine:
		ret
	}
}

void __fastcall OverrideShrinePatch(AutomapCell *pNewNode, AutomapCell *pCurNode)
{
	if ( (pNewNode->wCellNo < CELLNO_MYSHRINES) || (pNewNode->wCellNo >= (CELLNO_MYSHRINES+NUMOF_SHRINES) ) ) return;
	if ( pCurNode->wCellNo >= pNewNode->wCellNo ) return;
	pCurNode->fSaved = pNewNode->fSaved;
	pCurNode->wCellNo = pNewNode->wCellNo;
}

void __declspec(naked) OverrideShrinePatch_ASM()
{
	__asm {
//esi = ptr curr node
//ecx = ptr new node
		pushad
		mov edx,esi
		call OverrideShrinePatch
		popad
//original code
		mov edx,vD2AutomapCellListBaseAddr
		mov edx,[4*eax+edx]
		ret
	}
}

#endif