#include "stdafx.h"

#ifdef MODULE_VIEWTARGETUNITINFO


ViewUnitInfo viewStatUnit = {2,	(DWORD)-1,	(DWORD)-1 , NULL};
ViewUnitInfo viewEquUnit =	{1,	(DWORD)-1,	(DWORD)-1 , NULL};

UnitAny*  GetViewEquUnit(){
	return viewEquUnit.pUnit?viewEquUnit.pUnit:PLAYER;
}

UnitAny* GetViewStatUnit(){
	return viewStatUnit.pUnit?viewStatUnit.pUnit:PLAYER;
}

void SetViewUnit(){
	
	if ( viewEquUnit.pUnit != NULL ){
		if ( D2CheckUiStatus(UIVAR_INVENTORY) ){
			UnitAny *pUnit = D2GetUnitFromId(viewEquUnit.dwUnitId, viewEquUnit.dwUnitType);
			viewEquUnit.pUnit =  ( (pUnit&&pUnit->pInventory)?pUnit:PLAYER);
		}else{
			viewEquUnit.pUnit = NULL;
		}
	}

	if ( viewStatUnit.pUnit != NULL ){
		if ( D2CheckUiStatus(UIVAR_STATS) ){
			UnitAny *pUnit = D2GetUnitFromId(viewStatUnit.dwUnitId, viewStatUnit.dwUnitType);
			viewStatUnit.pUnit =  ( (pUnit&&pUnit->pInventory)?pUnit:PLAYER);
		}else{
			viewStatUnit.pUnit = NULL;
		}
	}
}

void ViewUnit(int nType) {

	UnitAny *pUnit = D2GetSelectedUnit();

	if (!pUnit || !CheckUnitSelect(pUnit)) return;
	ViewUnitInfo *pViewUnitInfo ; 
	if( nType==1 ){
		pViewUnitInfo = &viewEquUnit ; 
	}else if( nType==2 ){
		pViewUnitInfo = &viewStatUnit ; 
	}
	pViewUnitInfo->dwUnitId = pUnit->dwUnitId;
	pViewUnitInfo->dwUnitType = pUnit->dwUnitType;
	pViewUnitInfo->pUnit = pUnit;

	if ( !D2CheckUiStatus(pViewUnitInfo->dwUiNo)){
		D2SetUiStatus(pViewUnitInfo->dwUiNo, 0, 1);
	}

}


void __declspec(naked) GetViewingStatsPlayerPatch1_ASM()
{
	__asm {
		push eax
		call GetViewStatUnit
		cmp ebx,eax
		pop eax
		ret;
	}
}

void __declspec(naked) GetViewingStatsPlayerPatch2_ASM()
{
	__asm {
		push eax
		call GetViewStatUnit
		mov esi,eax
		pop eax
		ret;
	}
}

void __declspec(naked) GetUnitDrawEquipItemPatch_ASM()
{
	__asm {
		push eax;
		call GetViewEquUnit;
		mov esi, eax;
		pop eax;
		ret;
	}
}

void __declspec(naked) GetUnitDrawItemDescPath_ASM()
{
	__asm {
		push eax;
		call GetViewEquUnit;
		mov ebx, eax;
		pop eax;
		ret;
	}
}


void __declspec(naked) GetUnitTestHasItem_ASM()
{
	__asm {
//edi = default unit
		push eax
		mov eax, p_D2PlayerUnit
		mov eax, [eax]
		cmp edi, eax
		jnz viewinvold
		call GetViewEquUnit
		mov edi,eax
viewinvold:
		pop eax
//original code
		test eax,eax
		mov ecx, [edi+0x60]
		ret
	}
}

wchar_t* __fastcall GetUnitText(wchar_t* str, UnitAny* pUnit)
{
	*str = 0;
	if (pUnit->dwUnitType == UNITNO_PLAYER){
		return wsprintfW2(str, "%s", pUnit->pPlayerData->szName);
	}else{
		return wcscpy (str,	D2GetLocaleText(pUnit->pMonsterData->pMonsterTxt->wLocaleTxtNo));
	}

}

UnitAny *ViewDrawInvItemPatch()
{
	UnitAny *pUnit = GetViewEquUnit();
	if (pUnit != PLAYER) {
		wchar_t temp[80];
		wchar_t *p = GetUnitText(temp, pUnit);
		DrawCenterText(3, p, 484+DRAWOFFSET.x, 327-DRAWOFFSET.y, 8);
	}

	return pUnit;
}
void __declspec(naked) GetUnitDrawInvItemPatch_ASM(){
	__asm {
		call ViewDrawInvItemPatch;
		ret;
	}

}

void __declspec(naked) GetUnitProtectClickEquipPatch_ASM(){
	__asm {
		call GetViewEquUnit;
		mov ebx ,p_D2PlayerUnit
		mov ebx ,[ebx]
		cmp ebx, eax

		je oldcode

		push 0x13
		push ebx
		call D2ItemProtect
		add dword ptr [esp], 0xE1
		ret 4
oldcode:
		push [esp+4]
		call D2GetCursorItem
		ret 4
	}

}

void __declspec(naked) GetUnitProtectClickInvPatch_ASM(){
	__asm {
		push eax
		call GetViewEquUnit;
		mov ecx ,p_D2PlayerUnit
		mov ecx ,[ecx]
		cmp ecx, eax
		pop eax

		je oldcode

		push 0x13
		push ecx
		call D2ItemProtect
		add dword ptr [esp], 0x176
		ret

oldcode:
		mov ecx, dword ptr [ebp+0x08]
		mov edx, dword ptr [esp+0x30]
		ret
	}

}





#endif