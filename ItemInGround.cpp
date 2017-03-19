#include "stdafx.h"

#ifdef MODULE_ITEMINGROUND

BOOL  CheckItemVisible(UnitAny *pItem){
	// false 不显示 true 显示
	if( tHiddenItems.isOn ) return TRUE;

	//已辨识物品隐藏判定
	if( tShowIdentifiedItem.isOn && fPlayerInTown && pItem->pItemData->dwQuality>=3){
		if( D2CheckItemFlag(pItem, ITEMFLAG_IDENTIFIED, 0, "?") ) return TRUE;
	}

	//神符之语不隐藏
	if ( D2CheckItemFlag(pItem, ITEMFLAG_RUNEWORD, 0, "?") ) return TRUE;

	BYTE nColour = GetItemColour( pItem , nItemShowMode );
	if ( nColour == 0xFE ) return FALSE;
	return TRUE;

}

#endif