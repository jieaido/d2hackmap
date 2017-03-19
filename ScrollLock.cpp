#include "stdafx.h"

#ifdef MODULE_SCROLLLOCK

/*通过屏幕震动实现卷屏 ,需要ShakeScreenPatch*/
static int xMapOffset[9][5] , yMapOffset[9][5] ;
static int *pMapOffsetX , *pMapOffsetY;
static int nSrollIdx = 0;
void SetScrollMapPos(char xinc, char yinc)
{
	if (tScrollMap.isOn) {
		*pMapOffsetX += xinc*nMapScrollSpeed;
		*pMapOffsetY += yinc*nMapScrollSpeed;
		nMapScrollOffset[nSrollIdx][ACTNO][0] += xinc;
		nMapScrollOffset[nSrollIdx][ACTNO][1] += yinc;
	} else if ( *p_D2AutomapOn ) {
		AUTOMAPPOS.x += xinc*16;
		AUTOMAPPOS.y += yinc*16;
	}
}

void CenterMap()
{
	*pMapOffsetX = 0;
	*pMapOffsetY = 0;
}

void SetMapShake(){

	if (nScrollMode==3 && !fKeyRepeat){
		tScrollMap.isOn = 0;
		
		#ifdef MODULE_ROOMAREA
			tAutomapScreenArea.isOn = 0 ;
		#endif
	}

	pMapOffsetX  = &xMapOffset[nSrollIdx][ACTNO];
	pMapOffsetY  = &yMapOffset[nSrollIdx][ACTNO];

	if (tScrollMap.isOn) {
		MAPSHAKEX += *pMapOffsetX;
		MAPSHAKEY += *pMapOffsetY;
	}

}

void ScrollMap( int idx ) {
	switch ( nScrollMode ){
		case 2:
			if( idx == nSrollIdx){
				tScrollMap.isOn =  !tScrollMap.isOn;
			}else{
				tScrollMap.isOn = 1;
			}
			break;
		case 1:
			tScrollMap.isOn = 1 ;
			break;
		case 3:
			tScrollMap.isOn = 1;
			fKeyRepeat = TRUE ;
			dwKeyDown = tMapScrollKey[idx].key;
			break;
		default:
			break;
	}
	nSrollIdx = idx;

	#ifdef MODULE_ROOMAREA
		tAutomapScreenArea.isOn = tScrollMap.isOn ;
	#endif
	
}
void InitScrollLock(BOOL fInit){
	if ( fInit ){
		memset( tMapScrollKey,		0,		sizeof(tMapScrollKey) );
		memset( nMapScrollOffset,	0,		sizeof(nMapScrollOffset) );
		memset( yMapOffset,			0,		sizeof(yMapOffset) );
		memset( xMapOffset,			0,		sizeof(xMapOffset) );
		nMapScrollSpeed = 16 ;
		nScrollMode = 1 ;
		nSrollIdx = 0 ;
	}else{

		if ( nScrollMode >3 ) nScrollMode = 3;	
		for ( int i=1; i<=8; i++ ){

			tMapScrollKey[i].type = 3;
			tMapScrollKey[i].param = i;
			tMapScrollKey[i].funcParam = &ScrollMap;

			for ( int k=0 ; k<5 ; k++){

				xMapOffset[i][k] = nMapScrollOffset[i][k][0]*nMapScrollSpeed;			
				yMapOffset[i][k] = nMapScrollOffset[i][k][1]*nMapScrollSpeed;	

			}
		}
	}
}

void DrawScollOffset(wchar_t* wbuf ,int posy){
	if (tScrollMap.isOn){
		wsprintfW(wbuf, L"[%d,%d]",nMapScrollOffset[nSrollIdx][ACTNO][0] ,nMapScrollOffset[nSrollIdx][ACTNO][1]);
		DrawDefaultFontText(wbuf ,	INFOX , posy , 0 , 0 );
	}

}


#endif