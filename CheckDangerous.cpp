#include "stdafx.h"

#ifdef MODULE_CHECKDANGEROUS


void ProtectAction(wchar_t* wszShowMsg, int action = 1 , BYTE nCol = 8)
{
	//  1 exit game  , 2 back to home , 3 show message  4 drink
	wchar_t wszTemp[0x100];
	wcscpy( wszTemp	,	wszShowMsg);

	if ( fInGame ) {
		if (action == 1 ) {
			wcscat(wszTemp	,	L"Exit game.");
			D2ShowGameMessage(	wszTemp, nCol);
			ExitGame();
		} else if ( action == 2) {
			if ( fBackToTown==FALSE ){
				wcscat(wszTemp	,	L"Back to town.");
				D2ShowGameMessage( wszTemp, nCol );
				BackToTown();
			}
		} else if ( action == 3) {
			wcscat(wszTemp	,	L"Be careful.");
			D2ShowGameMessage( wszTemp, nCol );
		} else if ( action == 4) {
			//todo

		}
	}
}


void ChickenLife()
{
	if(PLAYER->dwMode==0x11) return ;

	if (tChickenLife.isOn || tChickenHostile.isOn){
		if (fPlayerInTown ) {
			fLifeProtectOn = FALSE ;
			return;
		}
		if ( fLifeProtectOn ) return ;
		DWORD dwLife = D2GetUnitStat(PLAYER, STAT_HP, 0)>>8;
		DWORD dwMaxlife = D2GetUnitStat(PLAYER, STAT_MAXHP, 0)>>8;
		
		if ( tChickenLife.isOn ){
			if( dwChickenLife && dwLife<=dwChickenLife){
				ProtectAction(L"<Hackmap>: Life below chicken threshold,", nChickenLifeAction);
				fLifeProtectOn = TRUE;
				return;
			}
			if( dwChickenLifePercent && dwLife*100 <= dwMaxlife*dwChickenLifePercent ){
				ProtectAction(L"<Hackmap>: Life below chicken threshold,", nChickenLifeAction);
				fLifeProtectOn = TRUE;
				return;
			}
		}
		if ( tChickenHostile.isOn ) {
			for (RosterUnit *pUnit = PLAYERLIST; pUnit; pUnit = pUnit->pNext ) {
				if ( TestPvpFlag(pUnit->dwUnitId , dwPlayerId) ==0 ){
					if ( (dwChickenHostileLife && dwLife<=dwChickenHostileLife) || (dwChickenHostileLifePercent && dwLife*100 <= dwMaxlife*dwChickenHostileLifePercent) ){
						ProtectAction(L"<Hackmap>: Life below chicken hostile threshold,",nChickenLifeAction);
						fLifeProtectOn = TRUE;
						return;
					}
				}
			}
		}
	}
	return;
}


void CheckDangerousPlayer( UnitAny  *pUnit ) {

	if ( fPlayerInTown ){
		fLifeProtectOn = FALSE ;
		return ;
	}
	if ( tChickenHostileNearby.isOn && pUnit->dwMode ){
		//校验敌对玩家
		if ( fLifeProtectOn==FALSE && TestPvpFlag(dwPlayerId , pUnit->dwUnitId) ==0){
			DWORD dwLife = D2GetUnitStat(PLAYER, STAT_HP, 0)>>8;
			DWORD dwMaxlife = D2GetUnitStat(PLAYER, STAT_MAXHP, 0)>>8;
			if ( (dwChickenHostileNearbyLife && dwLife<=dwChickenHostileNearbyLife) || (dwChickenHostileNearbyLifePercent && dwLife*100 <= dwMaxlife*dwChickenHostileNearbyLifePercent) ){
				ProtectAction(L"<Hackmap>: Life below chicken hostile nearby threshold,", nChickenLifeAction );
				fLifeProtectOn = TRUE;
			}
		}
	}

}

void CheckDangerousMonster( UnitAny  *pUnit ) {
	static DWORD statindexs[] = {STAT_FIRE_RESIST,
					STAT_COLD_RESIST, 
					STAT_LIGHTING_RESIST, 
					STAT_POSION_RESIST};


	if ( fPlayerInTown ){
		fDangerousMonsterActive = FALSE ;
		return ;
	}
	if( tChickenDangerousMonster.isOn && pUnit->dwMode && pUnit->dwMode!=0x0C){
		if ( fDangerousMonsterActive == FALSE ) {
			if (anDangerousMonster[pUnit->dwTxtFileNo][0] && anDangerousMonster[pUnit->dwTxtFileNo][0] < 5 && TestMonsterOnScreen(pUnit, PLAYER)) {
				
				int stat = GetUnitResist( PLAYER, statindexs[anDangerousMonster[pUnit->dwTxtFileNo][0]-1] );
 
				if (anDangerousMonster[pUnit->dwTxtFileNo][1] >= stat) {
					fDangerousMonsterActive = TRUE;
					ProtectAction(L"<Hackmap>: player's resistance below chicken threshold,",3);
				}

			}
		}
	}
}

#endif