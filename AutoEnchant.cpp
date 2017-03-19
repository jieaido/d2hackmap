#include "stdafx.h"

#ifdef MODULE_AUTOENCHANT

//发送强化数据包后，强化状态经常没置上，所以为每个unitid设置计时器，在计时结束前，不发送重复的数据包
//在每发送一次强化后，全局计时，计时结束才重新开始判定强化，减少无效数据包的发送
//此段调用很奇怪，增加锁，防止全局计时失效

void AutoEnchantLoop( UnitAny *pUnit ){

	static int delays = 0 ;//延时
	static int unitCount[2][1000] = {0,};  //1K

	if(fPlayerInTown){
		//出城后，等会开始
		delays = 1000;
		return;
	}
	
	if ( delays >0 ) {
		delays -- ;
		return;
	}
	
	DWORD dwUnitId = pUnit->dwUnitId ; 

	if ( pUnit->dwUnitType==UNITNO_PLAYER && dwUnitId == dwPlayerId) return; //不给自己强化

	if ( PLAYER->pSkill->pRightSkill->pSkillInfo->wSkillId !=52 ) return;//需要右键开启强化

	if ( pUnit->dwUnitType==UNITNO_MONSTER ){
		dwUnitId = D2GetMonsterOwner(pUnit->dwUnitId);
		if (dwUnitId == (DWORD)-1)return; //非玩家随从
	}
	
	if ( D2CheckUnitState(pUnit, 16) )return; //已强化

	if ( unitCount[pUnit->dwUnitType][pUnit->dwUnitId] >0 ) {
		//没强化状态，但计时未结束，不做强化动作
		unitCount[pUnit->dwUnitType][pUnit->dwUnitId] = unitCount[pUnit->dwUnitType][pUnit->dwUnitId] -1;
		return;
	}
	if ( TestPvpFlag( dwPlayerId, dwUnitId )>=2 ){
		//只能给盟友
		unitCount[pUnit->dwUnitType][pUnit->dwUnitId] = 2000; //开始计时
		delays = 800 ; //在下次发送前，全局计时

		BYTE castTP1[9] = {0x0D};
		*(DWORD*)&castTP1[1] = pUnit->dwUnitType;
		*(DWORD*)&castTP1[5] = pUnit->dwUnitId;
		D2SendPacket(sizeof(castTP1), 0, castTP1);		
	}
	return;
}

void AutoEnchant(UnitAny *pUnit) {
	
	static int lock = 0 ; 

	if( tAutoEnchant.isOn==0 ) return;

	if (lock==1)return;
	lock = 1;
	AutoEnchantLoop(pUnit);
    lock = 0;
	return ;

}


#endif