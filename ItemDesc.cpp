
#include "stdafx.h"

#ifdef MODULE_ITEMDESC

BOOL fViewSockFlag = FALSE;
BOOL fViewSocketableOn = FALSE;
wchar_t wszDescText[0x400] = {L'\0'};


/*物品显示*/
void __fastcall ItemDescPath( wchar_t *wszDesc , int xPos , int yPos , int unk1, int unk2 ){
	
	fViewSockFlag = TRUE;
	static int yPosition = 0 ;
	DWORD dwWidth, dwHeight;
	if ( fViewSocketableOn ){

		wcsrcat(wszDescText, L"\n\n");
		wcsrcat(wszDescText, wszDesc);
		D2GetTextAreaSize(wszDescText, &dwWidth, &dwHeight);
		yPos = yPosition + dwHeight;
		
	}else{

		wcscpy(wszDescText, wszDesc);
		D2GetTextAreaSize(wszDescText, &dwWidth, &dwHeight);
		yPosition = yPos - dwHeight;
		
	}

	wszDescText[0x3FF] = 0;
	D2DrawHoverText(wszDescText , xPos , yPos ,unk1 ,unk2);

	#ifdef MODULE_ITEMEXTINFO
		SetExtInfoPos(xPos,yPos,dwWidth,dwHeight);
	#endif

}


void __declspec(naked) __fastcall SocketViewCallRoutine(UnitAny *pUnitView, DWORD arg, void (__stdcall *func)(UnitAny*, DWORD))
{
	__asm {
		mov eax, 0x6654
		push edx
		push ecx
		call [esp+0x0c]
		ret 4
	}
}

void __stdcall ItemSocketViewPatch(void (__stdcall *func)(UnitAny*, DWORD), UnitAny *pUnitView, DWORD arg)
{
	fViewSockFlag = FALSE;

	SocketViewCallRoutine(pUnitView, arg, func);

	if ( fViewSockFlag && (tViewSocketable.isOn || tViewSocketBase.isOn) )	{

		fViewSocketableOn = TRUE;
		UnitAny *pUnit = VIEWITEMUNIT;

		if ( pUnit && pUnit->pInventory ) {

			UnitAny *pItem = D2GetFirstItemInInv(pUnit->pInventory);
			while (pItem) {

				VIEWITEMUNIT = pItem;

				SocketViewCallRoutine(pUnit, 1, func);

				pItem = D2GetNextItemInInv(pItem);

			}
		}

		fViewSocketableOn = FALSE;

		VIEWITEMUNIT = pUnit;

	}
}


void __declspec(naked) ItemSocketViewPatch_ASM()
{
	__asm {
		pop eax // exchange return address
		pop ecx
		push eax
		push ecx
		jmp ItemSocketViewPatch
	}
}


/*如果开启查看镶嵌物，只查看其实际生效的属性 */
void __declspec(naked) SocketItemStatViewPatch_ASM()
{
	__asm {
		cmp fViewSocketableOn, 0
		jz outcode
		pop esi // discard my return adress
		pop esi // restore esi
		pop ebx // restore ebx
		ret
outcode:
		mov ecx, 0xF9E
		ret
	}
}


/*设置是否查看明细属性*/
StatList *  __stdcall GetItemExtStatListPatch(UnitAny *pUnit, DWORD dwStatNo, DWORD dwListFlag) 
{
	if ( tViewSocketBase.isOn ) return 0;
	return D2GetStatListWithFlag(pUnit,dwStatNo,dwListFlag);

}

/*设置是否查看镶嵌物附带的属性*/
void __declspec(naked) ItemBasicStatPatch_ASM()
{
	__asm {
		cmp [tItemBasicStat.isOn], 1
		je quitcode
		cmp [tViewSocketBase.isOn],1
		je quitcode
	//org
		push dword ptr [esp+4]
		call D2GetFirstItemInInv
		ret 4
quitcode:
		xor eax, eax
		ret 4
	}
}


#endif