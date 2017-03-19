#include "stdafx.h"

#ifdef MODULE_ITEMNAME
	
BOOL ItemHaveLevel(BYTE nType)
{	
	if (nType==74)return FALSE;
	if (nType==4)return FALSE;
	if (nType==22)return FALSE;
	if (nType>=76 && nType<=81)return FALSE;
	if (nType>=91 && nType<=102)return FALSE;
	return TRUE;
}

void __fastcall ItemNamePatch(wchar_t *wscNameOld, UnitAny *pItem ,ItemTxt *pItemTxt ){
	wchar_t wscTemp[0x40];
	memset(wscTemp,0,sizeof(wscTemp));

	wchar_t wscName[0x100];
	memset(wscName,0,sizeof(wscName));
	wcscpy(wscName,wscNameOld);

	BYTE nColour = GetItemColour(pItem,0);
	int itemIndex = GetItemIndex(pItem->dwTxtFileNo);
	trimspaces(wscName);
	if (pItemTxt->nType==4) {// gold
		wcsrcat(wscName, wsprintfW2(wscTemp, "%d ", D2GetUnitStat(pItem, STAT_GOLD, 0) ) );
	}else{
		DWORD dwQuality =(pItem->pItemData->dwQuality-1)&7;
		if ( (nColour == (BYTE)-1 ) && pItemTxt->fQuest) {
			nColour = nQuestItemColour; //任务物品
		}

		if ( pItemTxt->fQuest && pItemTxt->fDiffCheck  && D2GetUnitStat(pItem, STAT_ITEMDIFFICULTY, 0)< DIFFICULTY ){
			nColour = (BYTE)-1 ;  //无效任务道具,原代码会校验，不着色
		}
		if ( D2CheckItemFlag(pItem, ITEMFLAG_BROKEN, 0, "?") ){
			nColour = 1 ; //损坏的道具
		};

		// ethereal
		if ( D2CheckItemFlag(pItem, ITEMFLAG_ETHEREAL, 0, "?") )
		{
			if (pItemTxt->dwMinDef>0 && (wszEtherealBugItemPrefix[0]||wszEtherealBugItemPostfix[0])){
				int mDef = D2GetUnitBaseStat(pItem, 31,0);
				int mMinDef = pItemTxt->dwMinDef;
				int mMaxDef = pItemTxt->dwMaxDef ;
				mMinDef = (int)(mMinDef * 1.5) ;
				mMaxDef = (int)(mMaxDef * 1.5) ;
				if ( mDef>mMaxDef && pItem->pItemData->dwQuality==2 && D2CheckItemFlag(pItem, ITEMFLAG_SOCKETED, 0, "?")  ){
					if (wszEtherealBugItemPrefix[0]){
						wcsrcat(wscName, wscolorcpy(wscTemp,wszEtherealBugItemPrefix,nColour));
					}
					if (wszEtherealBugItemPostfix[0]){
						wscolorcpy(wscName+wcslen(wscName),wszEtherealBugItemPostfix,nColour);
					}
				}

			}
			if (wszEtherealItemPrefix[0]){
				wcsrcat(wscName, wscolorcpy(wscTemp,wszEtherealItemPrefix,nColour));
			}
			if (wszEtherealItemPostfix[0]){
				wscolorcpy(wscName+wcslen(wscName),wszEtherealItemPostfix,nColour);
			}
		}
		// rune numbers
		if (tRuneNumbers.isOn && (pItemTxt->nType == 74)) {
			int bktnum = (pItemTxt->szCode[1]-'0')*10+(pItemTxt->szCode[2]-'0');
			wsprintfW(wscName+wcslen(wscName), L" (%d)", bktnum);
		}
	
		// socket number
		if (tSocketNumbers.isOn && D2CheckItemFlag(pItem, ITEMFLAG_SOCKETED, 0, "?") ) {
			wsprintfW(wscName+wcslen(wscName), L" (%d)", D2GetUnitStat(pItem, STAT_NUMSOCKETS, 0) );
		}

		// item level
		if (tItemLevel.isOn && ItemHaveLevel(pItemTxt->nType)) {
			wsprintfW(wscName+wcslen(wscName), L" (%ld)", pItem->pItemData->dwItemLevel);
		}
		
		// item value
		if (tItemValue.isOn && (pItemTxt->fQuest == 0) && D2CheckUiStatus(UIVAR_NPCTRADE)==0 ) {
			wsprintfW(wscName+wcslen(wscName), L" ($%d)", D2GetItemValue( PLAYER, pItem, DIFFICULTY, QUESTDATA, dwItemValueNpc[ACTNO], 1));
		
		}
		// unit number
		if (tUnitNumber.isOn) {
			wsprintfW(wscName+wcslen(wscName), L" [0x%X]", pItem->dwUnitId);
		}

		// item index
		if (tItemIndex.isOn) {
			wsprintfW(wscName+wcslen(wscName), L" [i%d]", itemIndex + 1 );
		}
		// item type
		if (tItemType.isOn) {
			wsprintfW(wscName+wcslen(wscName), L" [T%d]", pItemTxt->nType );
		}

		// item Qlevel
		if (tItemQLevel.isOn) {
			wsprintfW(wscName+wcslen(wscName), L" (Q:%ld)", pItemTxt->nQLevel);
		}
		// item Magiclevel
		if (tItemMLevel.isOn) {
			wsprintfW(wscName+wcslen(wscName), L" (M:%ld)", pItemTxt->nMagicLvl);
		}
		
		// item Alevel
		if (tItemALevel.isOn) {
			if (dwQuality==3 || dwQuality==5 || dwQuality==7){
				wsprintfW(wscName+wcslen(wscName), L" (A:%ld)", GetItemAlvl( pItem->pItemData->dwItemLevel,pItemTxt->nQLevel,pItemTxt->nMagicLvl) );
			}
		}
		
		if (tAfterCube.isOn)
		{
			if (dwQuality==3)
			{
				int iLvl = GetItemILvlAfterCube( 1 , pItem->pItemData->dwItemLevel ,D2GetUnitStat(PLAYER, STAT_LEVEL, 0) );
				wcsrcat(wscName, wsprintfW2(wscTemp, "[After Craft Ilvl: %ld Alvl: %ld]\n",iLvl,GetItemAlvl(iLvl,pItemTxt->nQLevel,pItemTxt->nMagicLvl)) );
			}
			else if (dwQuality==5)
			{
				int iLvl = GetItemILvlAfterCube( 2 , pItem->pItemData->dwItemLevel ,D2GetUnitStat(PLAYER, STAT_LEVEL, 0));
				wcsrcat(wscName, wsprintfW2(wscTemp, "[After Cube Ilvl: %ld Alvl: %ld]\n",iLvl,GetItemAlvl(iLvl,pItemTxt->nQLevel,pItemTxt->nMagicLvl)) );
			}
		}

		if ( D2CheckItemFlag(pItem, ITEMFLAG_RUNEWORD, 0, "?") ){
			if ( tLifePerLevel.isOn ){
				int iPerlvValue=D2GetUnitStat(pItem, 216, 0);
				if (iPerlvValue)
				{
					char strVal [10] ;
					DblToStr(((double)iPerlvValue)/2048,3,strVal);
					wcsrcat(wscName, wsprintfW2(wscTemp, "[%s life/level]\n",strVal) );
				}
			}
			if (tShowBaseED.isOn){
				int ed = 0 ;
				if( itemIndex<1000 ){//武器
					ed = GetUnitMagicStat(pItem, 0x11);
				}else{//防具
					ed = GetUnitMagicStat(pItem, 0x10);
				}
				wcsrcat(wscName, wsprintfW2(wscTemp, "[Base Ed: %ld%%]\n",ed) );

			}
		}
	
		// item file index
		if (tItemFileIndex.isOn) {
			wcsrcat(wscName, wsprintfW2(wscTemp, " [TXT:%d F:%d Type:%d]\n",pItem->dwTxtFileNo, D2GetItemFileIndex(pItem) ,pItemTxt->nType ) );
		}

	}
	if (nColour != (BYTE)-1) ColourD2String(wscName, nColour);

	wscName[124] = 0 ;
	wcscpy(wscNameOld,wscName);

}
void __declspec(naked) ItemNamePatch_ASM()
{
	__asm {
//ebx = ptr unit item
//edi = ptr item name string
//ebp = pItemTxt
		push ebx
		push ebp
		push edi

		mov ecx, edi
		mov edx, ebx
		push ebp
		call ItemNamePatch
		
		pop edi
		pop ebp
		pop ebx

		mov al, [ebp+0x12A]
		ret
	}
}


wchar_t * __fastcall OpenCubeStringPatch(wchar_t *wcstr, DWORD dwColour)
{
	BYTE nColour = (BYTE)anItemColours[2041][0][0][0][0];
	if ( nColour != (BYTE)-1){
		return ColourD2String(wcstr, nColour);
	}
	if ( nQuestItemColour != (BYTE)-1 ){
		return ColourD2String(wcstr, nQuestItemColour);
	}else{
		return  wcstr;
	}
}

void __declspec(naked) OpenCubeStringPatch_ASM()
{
	__asm {
	//edi = str
	//esi = col
	mov ecx, edi
	mov edx, esi
	call OpenCubeStringPatch
	ret 4
	}
}







#endif