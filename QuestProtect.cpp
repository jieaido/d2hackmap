#include "stdafx.h"

#ifdef MODULE_QUESTPROTECT

static BugQuestInfo aBugInfo[5] ;
static DWORD BugTimer = 0 ;
static BYTE BugTimerSet[10] = { 0 ,};
static DWORD dwLastAct = 0 ; 

void ReSetTimer(){
	BugTimer = GetTickCount();
	memset(BugTimerSet,	0,	10*sizeof(BYTE));
	SetCenterAlertMsg(FALSE , L"\0");
}

void InitBugInfo(){

	if( dwBugAlertTimes>10 ) dwBugAlertTimes = 10 ;

	aBugInfo[0].fEnable = 0;
	aBugInfo[1].fEnable = 0;

	aBugInfo[2].fEnable = &tBugKM.isOn;
	aBugInfo[2].nType = tBugKM.value;
	aBugInfo[2].nQuestNo = 22 ; 
	strcpy(aBugInfo[2].szMsg ,"BugKM") ;

	aBugInfo[3].fEnable = &tBugKD.isOn;
	aBugInfo[3].nType = tBugKD.value;
	aBugInfo[3].nQuestNo = 26 ; 
	strcpy(aBugInfo[3].szMsg ,"BugKD") ;

	aBugInfo[4].fEnable = &tBugKB.isOn;
	aBugInfo[4].nType = tBugKB.value;
	aBugInfo[4].nQuestNo = 40 ; 
	strcpy(aBugInfo[4].szMsg ,"BugKB") ;

}


void SetBugQuestStatus() {
	wchar_t wszTemp[512];
	int acts = EXPANSION ? 5 : 4 ; //资料片才有A5
	
	if (dwBugProtectLvl>DIFFICULTY) return;
	for(int i=0 ; i < acts ; i++ ){

		if ( aBugInfo[i].fEnable ){

			BOOL fPlayer = D2CheckQuestFlag(QUESTDATA	,aBugInfo[i].nQuestNo	,	0);
			BOOL fGame = D2CheckQuestFlag(GAMEQUESTDATA	,aBugInfo[i].nQuestNo	,	15);

			aBugInfo[i].nStatus = 0 ;
			if ( fGame==0 ){ //当前游戏可完成
				if ( fPlayer== 0 ) {//玩家还没完成指定任务
					aBugInfo[i].nStatus = 1 ;
					if ( aBugInfo[i].nType == 2 && *(aBugInfo[i].fEnable)){
						wsprintfW2(wszTemp, "<Hackmap>: Not A %s Room,will check when active" , aBugInfo[i].szMsg);
						D2ShowGameMessage(wszTemp, 8);
					}
					
				} else {//玩家已完成指定任务
					if ( tAlertNoBug.isOn ){
						wsprintfW2(wszTemp, "<Hackmap>: Not A %s Room" , aBugInfo[i].szMsg);
						D2ShowGameMessage(wszTemp, 8);
					}
				}
			}

		}

	}
	
	ReSetTimer();
	dwLastAct = ACT->dwActNo ;

}

void ShowBugInfo() { 

	if ( dwLastAct != ACTNO ) {
		dwLastAct = ACTNO;
		ReSetTimer();
		return;
	}
	if (dwBugProtectLvl>DIFFICULTY) return;
	if ( aBugInfo[ACTNO].nStatus==0 ) return ;

	if( aBugInfo[ACTNO].fEnable && *aBugInfo[ACTNO].fEnable ){
		
		if ( aBugInfo[ACTNO].nStatus == 1 && aBugInfo[ACTNO].nType==2 ) return;

		DWORD mysecs = (GetTickCount() - BugTimer)/1000;

		if (mysecs >= dwBugAlertTimes)
		{
			// Force quit game
			if ( tBugAutoQuit.isOn ){
				#ifdef MODULE_QUICKGAME
					if ( tQuickNextGame.key !=0 && tQuickNextGame.key != (BYTE)-1 ){
						QuickNextGame(1);
					}else{
						QuickExitGame();
					}
				#else
					ExitGame();
				#endif
			}

		}else{
			if (BugTimerSet[mysecs] == 0)
			{
				wchar_t wszTemp[512];
				BugTimerSet[mysecs] = 1;
				if ( tBugAutoQuit.isOn ){
					wsprintfW2(wszTemp, "%s Protect On, Will quit in %d secs", aBugInfo[ACTNO].szMsg, dwBugAlertTimes-mysecs);
					SetCenterAlertMsg(TRUE , wszTemp);
					return;
				} else {
					wsprintfW2(wszTemp, "<Hackmap>: Warning!!!!Not A %s Room!!!!(%d)" , aBugInfo[ACTNO].szMsg, dwBugAlertTimes-mysecs);
					D2ShowGameMessage(wszTemp, 8);
				}
				
			}
		}
	}
}

void __fastcall BugKDProtect(DWORD param2 )
{
  /*
  KD打开最后的封印： 89 0C
  */
	if ( param2 == 0x0C && ACTNO==3 && aBugInfo[3].nStatus==1 && aBugInfo[3].nType==2 ){
		aBugInfo[3].nStatus = 2;
		ReSetTimer();
	}

}

void __declspec(naked) RecvCommand_89_Patch_ASM()
{
  __asm
  {
	// ecx = aPacket[1] 
	push ecx;
    call BugKDProtect;
    pop ecx;
    
	cmp ecx, 0x20;
	jl orgjl
	ret
orgjl:
	add dword ptr[esp] ,7;
    ret
  }
}

void __fastcall BugKBProtect(BYTE *aPacket)
{
  /*
  Baal转身下去：5D 24 00 03 00 00 
  已完成任务的人不会收到
  */
  if (aPacket[1] == 0x24 && aPacket[2] == 0x00 && aPacket[3] == 0x03  )
  {
	  if ( ACTNO==4 && aBugInfo[4].nStatus==1 && aBugInfo[4].nType==2 ){
		 aBugInfo[4].nStatus = 2;
		 ReSetTimer();
	  }
  }

}

void __declspec(naked) RecvCommand_5D_Patch_ASM()
{
  __asm
  {
    push ecx;
    call BugKBProtect;
    pop ecx;
	
	pop edx;
	sub esp, 8;
	mov eax, dword ptr [ecx];
	push edx;
    ret
  }
}

void CheckUnitKM(){

	if ( ACTNO==2 && aBugInfo[2].nStatus == 1 && *(aBugInfo[2].fEnable) && aBugInfo[2].nType==2 ){
		if ( dwCurrentLevel == 102 ) {
			aBugInfo[2].nStatus = 2 ;
			ReSetTimer();
			return ;
		}
		for (RosterUnit *pUnit = PLAYERLIST; pUnit; pUnit = pUnit->pNext ) {

			if ( pUnit->dwLevelNo== 102 && TestPvpFlag( pUnit->dwUnitId , dwPlayerId )>=2) {
				aBugInfo[2].nStatus = 2 ;
				ReSetTimer();
				return ;
			}
			
		}

	}

	if ( ACTNO==4 && aBugInfo[4].nStatus == 1 && *(aBugInfo[4].fEnable) && aBugInfo[4].nType==2 ){
		if ( dwCurrentLevel == 132 ) {
			aBugInfo[4].nStatus = 2 ;
			ReSetTimer();
			return ;
		}
		for (RosterUnit *pUnit = PLAYERLIST; pUnit; pUnit = pUnit->pNext ) {

			if ( pUnit->dwLevelNo== 132 && TestPvpFlag( pUnit->dwUnitId , dwPlayerId )>=2) {
				aBugInfo[4].nStatus = 2 ;
				ReSetTimer();
				return ;
			}
			
		}
	}

}


void __fastcall DrawQuestPagePatch(int ypos, int xpos)
{
	if ( QUESTPAGE ==0 ) {//牛关
		int cow = D2CheckQuestFlag(QUESTDATA, 4, 10);
		if (cow) DrawCenterText(8, L"X", 300+DRAWOFFSET.x, 50-DRAWOFFSET.y, 1);
	}else if ( QUESTPAGE ==1 ) {//act2 bug
		int dru = D2CheckQuestFlag(QUESTDATA, 14, 5);
		if (dru) DrawCenterText(8, L"X", 300+DRAWOFFSET.x, 50-DRAWOFFSET.y, 1);
	}
}

void __declspec(naked) DrawQuestPagePatch_ASM()
{
	__asm {
		push eax
		call DrawQuestPagePatch
		pop eax
//original code
		cmp esi,0x116
		ret
	}
}


#endif