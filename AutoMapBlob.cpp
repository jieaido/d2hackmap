#include "stdafx.h"

#ifdef MODULE_AUTOMAPBLOB

void __fastcall DrawAutomapBlob(int xpos, int ypos, DWORD dwColor,UnitAny *pUnit)
{
	if (MINMAPTYPE) {
		xpos -= 1;
		ypos += 5;
	}
	DWORD celltype = 0;
	if ( pUnit) {
		celltype = pUnit->dwUnitType;
		if ( celltype==UNITNO_PLAYER ) {
			if ( pUnit->dwUnitId==dwPlayerId  ) celltype = 8;
		}else if ( celltype==UNITNO_MONSTER ){
			if (pUnit->dwMode==0x0C ) {
				celltype = 9 ;
			}else{
				MonsterTxt *pMonsterTxt = pUnit->pMonsterData->pMonsterTxt;
				if ( pUnit->pMonsterData->fUnique ) {
					celltype = 10 ;
				}else if ( pMonsterTxt->fNpc ) {
					celltype = 7 ;
				}else if ( pUnit->pMonsterData->fBoss ){//召唤者回城次后会失去boss标记
					if ( pMonsterTxt->Level[0]>0 ) celltype = 6 ;//影子，陷阱之类的也会被设置fboss标记
				}
			}
		}else if ( celltype==UNITNO_ITEM ){
			ItemTxt *pItemTxt = D2GetItemTxt( pUnit->dwTxtFileNo );
			if (pItemTxt){
				celltype = pItemTxt->nType+11;
			}
		}
	}
	if (!pUnitBlobCells[celltype]) {
		static char blines[][2] = {0,-2, 4,-4, 8,-2, 4,0, 8,2, 4,4, 0,2, -4,4, -8,2, -4,0, -8,-2, -4,-4, 0,-2};
		for (int i = 0; i < ARRAYSIZE(blines)-1; i++) {
			D2DrawLine(xpos+blines[i][0], ypos+blines[i][1], xpos+blines[i+1][0], ypos+blines[i+1][1], dwColor, 0xff);
		}
	} else {
		if( (BYTE)dwColor>0 )
		{//某些情况下游戏本身会产生黑色的图标，屏蔽掉
	
			if (tMousePosToggle.isOn)
			{
				POINT tMP;
				PreparePosForDraw(&tMP,D2GetPlayerXOffset()+MOUSEPOS.y,MOUSEPOS.x+D2GetPlayerYOffset());
				if ((tMousePosToggle.key == 1) || ((tMousePosToggle.key == 2) && (celltype ==8)))
				{
					DrawAutomapCell(pMousePosCell, tMP.x, tMP.y, (BYTE)tMousePosToggle.value);
				}
			}

			if ((celltype ==8) && (tMyBlodColorToggle.isOn))
			{				
				DrawAutomapCell(pUnitBlobCells[celltype], xpos, ypos,(BYTE)tMyBlodColorToggle.value);
			}
			else
			{
				DrawAutomapCell(pUnitBlobCells[celltype], xpos, ypos, (BYTE)dwColor);
			}
		}
	}

}


void __declspec(naked) ForceDrawBlob_ASM()
{
	__asm {
		add dword ptr [esp], 0x61
		ret
	}
}

void __declspec(naked) DrawBlobPath_ASM()
{
//jmp
//esi ==> pUnit
//[esp+4] ==> colour
//ecx = x pos
//eax = y pos

	__asm {
		mov edx , eax
		push esi
		push [esp+8]
		call DrawAutomapBlob
		ret 4
	}
}

void __declspec(naked) DrawPartyPlayerBlobPatch_ASM()
{
	__asm {
//dl = col
//ecx = x pos
//eax = y pos
		push 0
		push edx
		mov edx,eax
		call DrawAutomapBlob
		add dword ptr [esp], 0x36
		ret
	}
}


BYTE __fastcall HostilePlayerPatch(UnitAny *pUnit)
{
	return TestPvpFlag( pUnit->dwUnitId  , dwPlayerId)==0?nHostilePlayerColor:nNeutralPlayerColor;
}

void __declspec(naked) HostilePlayerColor_ASM()
{
	__asm {
		mov ecx, esi
		call HostilePlayerPatch
		mov cl, al
		ret
	}
}

BYTE __fastcall DrawPlayerTextPatch(UnitAny *pUnit)
{
	
	if (pUnit->dwMode==17) return 1;
	BYTE fPvPflag = TestPvpFlag( pUnit->dwUnitId , dwPlayerId );
	if ( fPvPflag==2 ) return nPartyTextColour;
	return fPvPflag==0?nHostileTextColour:nNeutralTextColour;

}

void __declspec(naked) DrawPlayerTextPatch_ASM()
{
	__asm {
		push ebx
		push edi
		push esi
		mov  ecx , esi
		call DrawPlayerTextPatch
		and eax,0x000000FF
		mov ebx,[esp+0x0C]	//返回地址
		mov [esp+0x0C],eax
		jmp ebx
	}
}



DWORD __fastcall MonsterBlobDesc( UnitAny *pMon ){
	
	if (pMon->dwMode && pMon->dwMode!=0x0C && D2GetMonsterOwner(pMon->dwUnitId)==(DWORD)-1){
		wchar_t temp[1024];
		memset(temp, L'\0' , sizeof(temp));
		MonsterData *pMonsterData = pMon->pMonsterData;
		if (pMonsterData->fBoss ) {
			int aura = 0, enchno;
			if ( tSuperUniqueNameToggle.isOn ){
				if ( pMon->pMonsterData->fUnique ){
					wscolorcpy(temp+wcslen(temp), pMonsterData->wszMonName,nMonsterTextCol);
				}
			}
			for (int i = 0; i < 9; i++) {
				enchno = pMonsterData->anEnchants[i];
				if (enchno == 0) break;
				if (enchno == 30) aura = 1;
				if (enchno < 32 && awszEnchantDescs[enchno][0] ) {
					wscolorcpy(temp+wcslen(temp), awszEnchantDescs[enchno] ,nMonsterTextCol);
				}
			}
			if (aura) {
				//NOTE :- testing if monster effected by aura, NOT source of aura
				static BYTE states[7] = {0x21, 0x23, 0x28, 0x2b, 0x2e, 0x1c, 0x31};
				for (int i = 0; i < 7; i++) {
					if (awszAuraDescs[i][0] && D2CheckUnitState(pMon, states[i]) ) {
						wscolorcpy(temp+wcslen(temp), awszAuraDescs[i] ,nMonsterTextCol);
					}
				}
			}
			if ( tBossNameToggle.isOn ){
				if ( pMonsterData->pMonsterTxt->fBoss == 1 && pMonsterData->wUniqueNo == 0){
					wscolorcpy(temp+wcslen(temp), pMonsterData->wszMonName,nMonsterTextCol);

				}
			}
		}
		static BYTE stats[6] = {0x24, 0x25, 0x27, 0x29, 0x2b, 0x2d};
		for (int i = 0; i < 6; i++) {
			if (awszImmuneDescs[i][0] && D2GetUnitStat(pMon, stats[i], 0) >= 100) {
				wscolorcpy(temp+wcslen(temp), awszImmuneDescs[i] ,nMonsterTextCol);
			}
		}
		if(temp[0]){
			POINT ptObj;
			PreparePosForDraw(&ptObj,pMon->pMonPath->dwMapPosX,pMon->pMonPath->dwMapPosY);

			if ( nSuperUniqueDescFont>0 && pMon->pMonsterData->fUnique){
				DrawCenterText(nSuperUniqueDescFont,	temp,	ptObj.x,	ptObj.y-10,	nMonsterTextCol);
			}else{
				DrawCenterText(6,	temp,	ptObj.x,	ptObj.y-10,	nMonsterTextCol);
			}
		}
	}
	return MAPNAMON;
}

void __declspec(naked) MonsterBlobDescPatch_ASM()
{
	__asm {
//esi = ptr unit
		mov ecx,esi
		push ebx
		push ebp
		call MonsterBlobDesc
		pop ebp
		pop ebx
		ret
	}
}


BYTE __fastcall MonsterBlobCol(UnitAny *pMon)
{
	if ( tAutomapMonsters.isOn ) {
		

		DWORD dwOwnerId = D2GetMonsterOwner(pMon->dwUnitId);

		if (anMonsterColours[pMon->dwTxtFileNo] != (BYTE)-1) return anMonsterColours[pMon->dwTxtFileNo];

		if ( dwOwnerId != (DWORD)-1 ){
			BYTE fPvpFlag = TestPvpFlag( dwOwnerId , dwPlayerId );
			//队伍中，自己的显示0xcb 队友的0x81
			if ( fPvpFlag==2 )return nFriendMinionColor;
			if ( fPvpFlag==3 )return nPlayerMinionColor;
			return fPvpFlag==0?nHostilePlayerColor:nNeutralPlayerColor;
		}
		
		if (pMon->pMonsterData->fChamp ) return nMonsterChampColor;
		if (pMon->pMonsterData->fMinion ) return nMonsterMinionColor;
		if (pMon->pMonsterData->fBoss) 
		{
			if ( pMon->pMonsterData->fUnique && nSuperUniqueColor!=(BYTE)-1)
				return nSuperUniqueColor;
			else
				return nMonsterBossColor;
		}
		return nMonsterNormalColor;
	}
	return -1;
}

BYTE __fastcall CorpseBlobCol(UnitAny *pMon){
	
	if ( tAutomapCorpse.isOn ) {
		BOOL flag = D2CheckCorpseCanUse(pMon,0);
		if (flag) {
			if (anMonsterCorpseColors[pMon->dwTxtFileNo] == (BYTE)-2) {
				if (pMon->pMonsterData->fChamp ) return nChampionCorpseColor;
				if (pMon->pMonsterData->fMinion ) return nMinionCorpseColor;
				if (pMon->pMonsterData->fBoss ) return nBossCorpseColor;
				return nMonsterNormalColor;
			}
			return anMonsterCorpseColors[pMon->dwTxtFileNo];
		}
	}
	return -1;
}



BYTE __fastcall ObjectBlobCol(UnitAny *pObject){
	
	ObjectTxt *pObjTxt = pObject->pObjectData->pObjectTxt;
	if ( tAutomapChests.isOn && !pObject->dwMode ) {
		if (pObjTxt->nSelectable[0] && 
				(
				(pObjTxt->nOperateFn == 1) || //bed, undef grave, casket, sarc
				(pObjTxt->nOperateFn == 3) || //basket, urn, rockpile, trapped soul
				(pObjTxt->nOperateFn == 4) || //chest, corpse, wooden chest, buriel chest, skull and rocks, dead barb
				(pObjTxt->nOperateFn == 5) || //barrel
				(pObjTxt->nOperateFn == 7) || //exploding barrel
				(pObjTxt->nOperateFn == 14) || //loose bolder etc....*
				(pObjTxt->nOperateFn == 19) || //armor stand
				(pObjTxt->nOperateFn == 20) || //weapon rack
				(pObjTxt->nOperateFn == 33) || //writ
				(pObjTxt->nOperateFn == 48) || //trapped soul
				(pObjTxt->nOperateFn == 51) || //stash
				(pObjTxt->nOperateFn == 68)    //evil urn
				)
			) return (pObject->pObjectData->fChestLocked) ? nLockedChestColor : nClosedChestColor;
	}
	if ( pObject->dwMode == 2 && pObjTxt->nSubClass&33 ){//已经用掉的shine  1或32(井水)
		POINT ptObj;
		PreparePosForDraw(&ptObj,pObject->pItemPath->dwMapPosX,pObject->pItemPath->dwMapPosY);
		wchar_t temp[20] = {L'X',L'\0'};
		DrawCenterText(5, temp, ptObj.x, ptObj.y, 2);
	}
	return -1;
}


BYTE __fastcall MissileBlobCol(UnitAny *pMissile){
	if ( tAutomapMissiles.isOn && !(pMissile->dwFlags1&0x00010000)) {//非死亡的
		if (anMissileColours[pMissile->dwTxtFileNo] == (BYTE)-2) {
			DWORD dwOwnerId = 0;
			if ( pMissile->dwOwnerType == UNITNO_PLAYER ){
				dwOwnerId =  pMissile->dwOwnerId;
			}else if ( pMissile->dwOwnerType ==UNITNO_MONSTER ){
				dwOwnerId =  D2GetMonsterOwner(pMissile->dwOwnerId);
			}
			if ( (int)dwOwnerId > 0 ) {
				BYTE fPvPFlag = TestPvpFlag( dwOwnerId ,dwPlayerId );
				if ( fPvPFlag > 0 )return nTracerMissileColor;
				if ( fPvPFlag ==0 ) {
					return (pMissile->pMonPath->pTargetUnit == PLAYER) ? nGuidedMissileColor : nHostileMissileColor;
				} 
			}
			if (dwOwnerId==0) return nOtherMissileColor;
			return nHostileMissileColor;
		}
		return anMissileColours[pMissile->dwTxtFileNo];
	}
	return -1;
}


BYTE __fastcall MixedBlobColPatch(UnitAny *pUnit)
{
	switch( pUnit->dwUnitType ){
		case UNITNO_MONSTER:
			if (pUnit->dwMode && pUnit->dwMode != 0x0C) return MonsterBlobCol( pUnit );
			return CorpseBlobCol( pUnit );
		case UNITNO_OBJECT:
			return ObjectBlobCol( pUnit );
		case UNITNO_MISSILE:
			return MissileBlobCol( pUnit );
		
		#ifdef MODULE_ITEMDEFINE
		case UNITNO_ITEM:
			if ( tAutomapItems.isOn ){
				BYTE color = GetItemColour( pUnit , nItemShowMode );
				if ( color==(BYTE)-2) return -1;
				return color;
			}
		#endif

		default:
			return -1;

	}
}

void __declspec(naked) MixedBlobColPatch_ASM()
{
	__asm {
//esi = ptr unit
//ebx = ptr colour
//return eax = draw flag
		mov ecx,esi
		push ebx
		call MixedBlobColPatch
		pop ebx
		test al ,al
		jz oldcode
		mov [ebx],al
		sub al,-4
		setb al
oldcode:
		movzx eax,al
		pop esi
		add esp, 0x0C
		ret
	}
}





#endif