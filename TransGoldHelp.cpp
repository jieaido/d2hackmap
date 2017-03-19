#include "stdafx.h"

#ifdef MODULE_TRANSGOLDHELP
int __fastcall SetGoldPatch(int iType){

	int gold = *p_D2GoldInTranBox;

	if ( iType==4 && gold >0){//从箱子往身上转移金钱，且金额大于0
		//计算是否超过能转移的最大值，如果超过，取最大值
		int goldstash = D2GetUnitStat(PLAYER, STAT_GOLD ,0);
		int lvl = D2GetUnitStat(PLAYER, STAT_LEVEL ,0);
		int maxgold = lvl*10000 - goldstash ;
		if ( gold>maxgold ) gold = maxgold ;
		*p_D2GoldInTranBox = gold;
	}
	return gold;
}

void __declspec(naked) SetGoldPatch_ASM()
{
	__asm{
		mov ecx ,eax
		call SetGoldPatch
		mov edx ,eax
		ret
	}
}

void __declspec(naked) SetDefaultGoldPatch_ASM()
{
	__asm{
		
		cmp ebx , 4
		je nojmp
		cmp ebx , 6
		je nojmp
		add dword ptr [esp] , 0x30
nojmp:
		ret
	}
}


#endif