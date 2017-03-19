#include "stdafx.h"

#ifdef MODULE_QUICKSWAPITEM


void  MoveItem(D2MSG *pMsg ){
	
	static InventoryType invTypes[] = {   //left和bottom已经偏移了格子一半大小
		{0, 430, 325, 10, 4, 29, 29}, // Inventory
		{4, 165, 152, 6, 8, 29, 29}, // Stash
		{3, 220, 220, 3, 4, 29, 29}, // Cube
		{4, 165, 345, 6, 4, 29, 29}, // Stash_Classic
		{2, 110, 325, 10, 4, 29, 29}, // Trade 1 for others trade
	};
	
	UnitAny *pItem = PLAYER->pInventory->pCursorItem;

	if (!pItem) return ;  //手上没东西
	
	int invtype = 0;
	if ( D2CheckUiStatus(UIVAR_STASH) ) {

		if ( EXPANSION ) invtype = 1; 
		else invtype = 3; //非资箱子

	} else if ( D2CheckUiStatus(UIVAR_CUBE) ){

		invtype = 2;

	} else if ( D2CheckUiStatus(UIVAR_PPLTRADE) ) {

		invtype = 4; //交易窗体

	}

	if ( invtype>0 ) {//左边开

		InventoryType *pInvType = (pMsg->xpos < SCREENSIZE.x/2) ? &invTypes[0] : &invTypes[invtype];

		if (pInvType) {

			DWORD dwBoxType = D2GetBoxType(PLAYER, pInvType->invType, EXPANSION);
			for (int x = 0; x < pInvType->nGridXs; ++x) {
				for (int y = 0; y < pInvType->nGridYs; ++y) {

					int xpos = pInvType->left + x*pInvType->nGridWidth;
					int ypos = pInvType->bottom + y*pInvType->nGridHeight;
					int gridcount = 0;
					int itemcount = 0;
					SendMessage(pMsg->hwnd, WM_MOUSEMOVE, pMsg->wParam, MAKELONG(xpos, ypos));
					D2CheckInvLocation(PLAYER->pInventory, pItem, *p_D2CursorInvGridX, *p_D2CursorInvGridY, dwBoxType, &gridcount, &itemcount, pInvType->invType);
					if ( itemcount==0 ) {
						SendMessage(pMsg->hwnd, WM_LBUTTONDOWN, pMsg->wParam, MAKELONG(xpos, ypos));
						SendMessage(pMsg->hwnd, WM_LBUTTONUP, pMsg->wParam, MAKELONG(xpos, ypos));
						x = y = 1000; // break;
					}

				}

			}
	
			SendMessage(pMsg->hwnd, WM_MOUSEMOVE, pMsg->wParam, pMsg->lParam);
		}

	}else if (tQuickDropToggle.isOn){
		
		if ( D2CheckUiStatus(UIVAR_INVENTORY) && 
			!D2CheckUiStatus(UIVAR_STATS) && 
			!D2CheckUiStatus(UIVAR_QUEST) && 
			!D2CheckUiStatus(UIVAR_PARTY) &&
			!D2CheckUiStatus(UIVAR_PET) &&
			!D2CheckUiStatus(UIVAR_QUESTSCROLL) ){

			int xpos = 230;
			int ypos = 200;
			SendMessage(pMsg->hwnd, WM_MOUSEMOVE, pMsg->wParam, MAKELONG(xpos, ypos));
			SendMessage(pMsg->hwnd, WM_LBUTTONDOWN, pMsg->wParam, MAKELONG(xpos, ypos));
			SendMessage(pMsg->hwnd, WM_LBUTTONUP, pMsg->wParam, MAKELONG(xpos, ypos));
			SendMessage(pMsg->hwnd, WM_MOUSEMOVE, pMsg->wParam, pMsg->lParam);

		}

	}

}

void __stdcall RButtonUpHandlerPatch(D2MSG *pMsg)
{

	if( fInGame==FALSE )return;

	if (tRightClickSwap.isOn && pMsg->dwMessage == WM_RBUTTONUP) {
		
		MoveItem( pMsg );

	}
	StopShake();
}


void __declspec(naked) RButtonUpHandlerPatch_ASM()
{
	__asm {
		push [esp+8];
		call RButtonUpHandlerPatch;
//oldcode:
		mov eax, p_D2InGame;
		mov eax, [eax];
		ret;
	}
}

void __declspec(naked) RButtonInTradePatch_ASM()
{
	__asm {
		push [esp+4];
		call RButtonUpHandlerPatch
		jmp D2Storm511
	}
}



//Ctrl+点击控制
//在联网模式，由于需要等待数据包返回才能拿起物品，所以在ButtonUp中不一定能处理好
//采用先在LButtonUp开始计时，激活游戏循环判定，直到处理完毕


static int nClickStatus = 0;    //是否Ctrl+点击事件
static BOOL fSwapProc = FALSE;  //是否已开始处理
static BOOL fSwapProcLoop = FALSE; //是否交给游戏循环处理
static D2MSG unDealMsg; //LButtonUp消息结构缓存
static DWORD dwSwapTimer;//计时器
void DealCtrlClick(){

	if ( fSwapProcLoop == TRUE ){
		
		if ( GetTickCount()-dwSwapTimer> PING +10 ) {
			UnitAny *pItem = PLAYER->pInventory->pCursorItem;
			if ( pItem){
				MoveItem( &unDealMsg );
				fSwapProc = FALSE;
				nClickStatus = 0;
				fSwapProcLoop = FALSE;
				dwSwapTimer = GetTickCount();
			}
		}
	}

}


void __declspec(naked) CtrlClickHandlerPatch_ASM()
{
	__asm {
		je noNpc 
		ret//如果NPC，跳过处理
noNpc:
		cmp [tCtrlClickSwap.isOn] , 0
		jz orgjz

		cmp [fSwapProc] , 1  //处理中
		je orgjz

		mov [nClickStatus],1
		add dword ptr [esp] ,0x12D //强制拿起物品
		xor eax ,eax
		ret
orgjz:	
		add dword ptr [esp] ,0x141
		ret
	}
}


void __stdcall LButtonUpHandlerPatch(D2MSG *pMsg)
{
	
	if ( fSwapProc ) return ;
	if ( nClickStatus==0 ) return ;

	fSwapProc = TRUE;
	fSwapProcLoop = FALSE;
	
	dwSwapTimer = GetTickCount();
	fSwapProcLoop = TRUE;
	unDealMsg = *pMsg;

	/*UnitAny *pItem = PLAYER->pInventory->pCursorItem;
	if ( pItem){
		Sleep(150);
		MoveItem( pMsg );
	}else{
		fSwapProcLoop = TRUE;
		unDealMsg = *pMsg;
		return;
	}*/

	//fSwapProc = FALSE;
	//nClickStatus = 0;

}
void __declspec(naked) LButtonUpHandlerPatch_ASM()
{
	//esp+4  = pMsg
	__asm {
		push ebp
		push ebx

		push [esp+0xC]
		call D2Storm511    //原始调用，先调用将LButtonUp消息处理掉

		push [esp+0xC]
		call LButtonUpHandlerPatch

		pop ebx
		pop ebp
		ret 4
	}
}


#endif