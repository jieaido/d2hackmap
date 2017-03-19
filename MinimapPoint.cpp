#include "stdafx.h"
//基于AutomapCell,在RoomPatch中运行

#ifdef MODULE_MINIMAPPOINT

extern MinimapConfig aMinimapConfigs[140];
MinimapCell aMinimapCells[140][30];//游戏中存在的可指向坐标
int mimimapCells[140] = {0} ;
MinimapPoint aMinimapPoints[140];//实际作用的指向坐标

void AddMinimapCell( DrlgLevel* pDrlgLevel , short cellno ,short xpos , short ypos ){
	DWORD dwLevelNo = pDrlgLevel->dwLevelNo;
	if( dwLevelNo == 45 ) dwLevelNo = 44; // Change Valley of Snakes to Lost City
	if( dwLevelNo == 17 ) dwLevelNo = 3; // 埋骨之地改为冰冷之原
	if (cellno < 0 ) cellno = -cellno;
	if ( dwLevelNo==46 && pDrlgLevel->pDrlgMisc->dwStaffTombLvl == cellno)cellno=300 ;//方便指向设定
	if ( dwLevelNo >=140 || mimimapCells[dwLevelNo] >= 30 ) return ;

	if ( (dwLevelNo == 4 && cellno == 314)) { 
		for ( int i = 0 ; i < mimimapCells[dwLevelNo] ; i++){
			if( aMinimapCells[dwLevelNo][i].cellno == cellno ) return;
		}
	}
	
	aMinimapCells[dwLevelNo][ mimimapCells[dwLevelNo] ].cellno = cellno;
	aMinimapCells[dwLevelNo][ mimimapCells[dwLevelNo] ].xpos = xpos;
	aMinimapCells[dwLevelNo][ mimimapCells[dwLevelNo] ].ypos = ypos;
	mimimapCells[dwLevelNo]++;
}

void ResetMiniCells(){
	memset( aMinimapCells ,				0	,		sizeof(aMinimapCells) );
	memset( mimimapCells ,				0	,		sizeof(mimimapCells) );
	memset( aMinimapPoints ,			0	,		sizeof(aMinimapPoints) );
}


void BuildMiniMapPoint( DWORD dwAct ){
	DWORD lvlfirst,lvlend;
	if ( dwAct==5 ) {
		lvlfirst = actlvls[0] ;
		lvlend = actlvls[5];
	}else{
		lvlfirst = actlvls[dwAct] ;
		lvlend = actlvls[dwAct+1] ;
	}

	for ( DWORD i=lvlfirst; i<lvlend; i++ ){
		aMinimapPoints[i].nPoints = 0 ;
		MinimapConfig *pConfig = &aMinimapConfigs[i];
		for ( int j=0 ; j < pConfig->nPoints; j++ ){
			for( int k=0; k<mimimapCells[i] ; k++){
				if( pConfig->aPoint[j].wPointNo==aMinimapCells[i][k].cellno  && pConfig->aPoint[j].fFlag ){
					if ( pConfig->aPoint[j].nColour ==(BYTE)-1 ){
						aMinimapPoints[i].aPoint[aMinimapPoints[i].nPoints].nColour = nMinimapCellCol ;
					}else{
						aMinimapPoints[i].aPoint[aMinimapPoints[i].nPoints].nColour = pConfig->aPoint[j].nColour ;
					}
					aMinimapPoints[i].aPoint[aMinimapPoints[i].nPoints].xpos = aMinimapCells[i][k].xpos ;
					aMinimapPoints[i].aPoint[aMinimapPoints[i].nPoints].ypos = aMinimapCells[i][k].ypos ;
					aMinimapPoints[i].nPoints++;
				}
			}
		}
	
	}

}


BOOL AdjustPosition(POINT *ptPlayer, POINT *ptObject, POINT *ptLine)
{
	//终点位置为 nMinimapSize/10 处 , 线条于1/15处
	int xDistance = ptObject->x-ptPlayer->x;
	int yDistance = ptObject->y-ptPlayer->y;
	
	if ( abs(xDistance)<15 && abs(yDistance)<15 ){
		return false;
	}else{
		
		ptObject->x = (LONG)( ptPlayer->x + nMinimapSize*xDistance/10);
		ptObject->y = (LONG)( ptPlayer->y + nMinimapSize*yDistance/10);

		ptLine->x = (LONG)( ptPlayer->x + 2*nMinimapSize*xDistance/30);
		ptLine->y = (LONG)( ptPlayer->y + 2*nMinimapSize*yDistance/30);
		return true;
	}
}


void DrawMinimapPoint(){
	if ( tMinimap.isOn ) {
		for ( int i=0 ; i<aMinimapPoints[LEVELNO].nPoints ; i ++){
			BYTE colour = aMinimapPoints[LEVELNO].aPoint[i].nColour;
			int xpos = aMinimapPoints[LEVELNO].aPoint[i].xpos*10;
			int ypos = aMinimapPoints[LEVELNO].aPoint[i].ypos*10;
			
			//修改此处，使指向不受scrolllock和地图移动影响
			POINT ptObj,ptPlayer , ptLine; 
			PreparePosForDraw(&ptPlayer,PLAYER->pMonPath->dwMapPosX,PLAYER->pMonPath->dwMapPosY);
			PreparePosForDraw(&ptObj , xpos, ypos);

			if ( AdjustPosition(&ptPlayer, &ptObj, &ptLine) ){

				if (pMinimapObjectCell) {
					DrawAutomapCell(pMinimapObjectCell, ptObj.x, ptObj.y,colour);
				}else{
					wchar_t temp[20] = {L'*'};
					ColourD2String(temp, colour);
					DrawCenterText(6, temp, ptObj.x, ptObj.y, colour);
				}
				D2DrawLine(ptPlayer.x, ptPlayer.y, ptLine.x, ptLine.y, colour, -1);

			}
		}
	}

	if ((tMousePosToggle.isOn == 1) && (tMousePosToggle.key == 3))
	{
		POINT tMP;
		PreparePosForDraw(&tMP,D2GetPlayerXOffset()+MOUSEPOS.y,MOUSEPOS.x+D2GetPlayerYOffset());
		DrawAutomapCell(pMousePosCell, tMP.x, tMP.y, (BYTE)tMousePosToggle.value);
	}

}

#endif