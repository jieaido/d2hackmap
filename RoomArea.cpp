#include "stdafx.h"

#ifdef MODULE_ROOMAREA

//ÓÎÏ·ÇøÓò¿é

void ComputePos(POINT* pos, int x, int y)
{
	MapToAbsScreen(pos , x , y );
	PreparePosForDraw(pos , pos->x , pos->y );
}

void ScreenToAutomapRelative(POINT* pos, int x, int y)
{
	x += D2GetPlayerXOffset();
	y += D2GetPlayerYOffset();
	PreparePosForDraw(pos, x, y);
}

void DrawRoom2(DrlgRoom2 *pRoom2, DWORD dwColour)
{
	POINT ptTopLeft, ptTopRight, ptBottomLeft, ptBottomRight;
	
	ComputePos(&ptTopLeft,		 pRoom2->dwPosX,					pRoom2->dwPosY);
	ComputePos(&ptTopRight,		 pRoom2->dwPosX+pRoom2->dwSizeX,	pRoom2->dwPosY);
	ComputePos(&ptBottomLeft,	 pRoom2->dwPosX,					pRoom2->dwPosY+pRoom2->dwSizeY);
	ComputePos(&ptBottomRight,   pRoom2->dwPosX+pRoom2->dwSizeX,	pRoom2->dwPosY+pRoom2->dwSizeY);

	D2DrawLine(ptTopLeft.x,		ptTopLeft.y,	ptTopRight.x,	 ptTopRight.y,		dwColour, -1);
	D2DrawLine(ptBottomLeft.x,	ptBottomLeft.y, ptBottomRight.x, ptBottomRight.y,	dwColour, -1);
	D2DrawLine(ptTopLeft.x,		ptTopLeft.y,	ptBottomLeft.x,  ptBottomLeft.y,	dwColour, -1);
	D2DrawLine(ptTopRight.x,	ptTopRight.y,	ptBottomRight.x, ptBottomRight.y,	dwColour, -1);
}


void RoomPatch(){
	
	if (tAutomapReadyRoom.isOn) {
		DrlgRoom1 *pRoom1 = ACT->pRoom1;
		while (pRoom1 && pRoom1->pRoom2) {
			DrawRoom2(pRoom1->pRoom2, nAutomapReadyColors);
			pRoom1 = pRoom1->pNext;	
		}
	}

	if (tAutomapActiveRoom.isOn) {
		DrlgRoom1 *pRoom1 = PLAYER->pMonPath->pRoom1;
		for (DWORD i = 0; i < pRoom1->dwRoomsNear; i++ ) {
			DrawRoom2( pRoom1->paRoomsNear[i]->pRoom2,nAutomapActiveRoomColors );
		}

	}
	if (tAutomapScreenArea.isOn) {
		POINT ptTopLeft, ptTopRight, ptBottomLeft, ptBottomRight;
		ScreenToAutomapRelative(&ptTopLeft,		 0,					0);
		ScreenToAutomapRelative(&ptTopRight,	SCREENSIZE.x,		0);
		ScreenToAutomapRelative(&ptBottomLeft,	0,					SCREENSIZE.y-48);
		ScreenToAutomapRelative(&ptBottomRight, SCREENSIZE.x,		SCREENSIZE.y-48);

		D2DrawLine(ptTopLeft.x,		ptTopLeft.y,	ptTopRight.x,		ptTopRight.y,	 nAutomapScreenColors, -1);
		D2DrawLine(ptBottomLeft.x,	ptBottomLeft.y,	ptBottomRight.x,	ptBottomRight.y, nAutomapScreenColors, -1);
		D2DrawLine(ptTopLeft.x,		ptTopLeft.y,	ptBottomLeft.x,		ptBottomLeft.y,  nAutomapScreenColors, -1);
		D2DrawLine(ptTopRight.x,	ptTopRight.y,	ptBottomRight.x,	ptBottomRight.y, nAutomapScreenColors, -1);
	}
	DrawMousePointer();
	/*if (tMouseScrollMapToggle.isOn) {
		DrawMousePointer();
	}*/
	#ifdef MODULE_MINIMAPPOINT
		DrawMinimapPoint();
	#endif
}
void __declspec(naked) RoomPatch_ASM()
{
	__asm {
		call RoomPatch
		mov ecx, p_D2AutomapLayer
		mov ecx, [ecx]
		ret
	}
}



#endif