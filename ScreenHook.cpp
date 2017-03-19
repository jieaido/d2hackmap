#include "stdafx.h"

#ifdef MODULE_SCREENHOOK

static D2ScreenHookStruct D2ScreenHook[10];

void UpdateExp() {
	if( fInGame==FALSE )return;

	char temp_s[512];
	UnitAny *ptPlayer = PLAYER;
	
	int exp = D2GetUnitStat(ptPlayer, STAT_EXP, 0);
	DWORD lvl = D2GetUnitStat(ptPlayer, STAT_LEVEL, 0);
	DWORD player_class = ptPlayer->dwTxtFileNo;

	int nextlvlexp = D2GetMinExpToLevel(player_class, lvl);
	int currentlvlexp = 0;
	if (lvl>1)
	{
		currentlvlexp = D2GetMinExpToLevel(player_class, lvl-1);
	}
	
	int totalexpneedtoupgrade = nextlvlexp - currentlvlexp;
	int currentlvlgainedexp = exp - currentlvlexp;
	int currentgamegainedexp = exp - currentgameexp;
	if (currentgamegainedexp > currentlvlgainedexp) currentgamegainedexp = currentlvlgainedexp;

	if (tShowExp.value==2)
	{
		sprintf(temp_s,"+Exp:[%.2f%%%%]%d", ((float)(currentgamegainedexp)*100)/((float)totalexpneedtoupgrade),currentgamegainedexp);
		wsprintfW2(D2ScreenHook[0].wszMsg, temp_s);
		sprintf(temp_s,"Lv%d:[%.2f%%%%]%d / %d", lvl,((float)currentlvlgainedexp*100)/((float)totalexpneedtoupgrade), currentlvlgainedexp,totalexpneedtoupgrade);
	}
	else
	{
		if(currentgamegainedexp<0){
			sprintf(temp_s,"Lv%d:[%.2f%%%%][%.2f%%%%]%d", lvl,((float)currentlvlgainedexp*100)/((float)totalexpneedtoupgrade),((float)(currentgamegainedexp)*100)/((float)totalexpneedtoupgrade), currentgamegainedexp);
		}else{
			sprintf(temp_s,"Lv%d:[%.2f%%%%][+%.2f%%%%]%d", lvl,((float)currentlvlgainedexp*100)/((float)totalexpneedtoupgrade),((float)(currentgamegainedexp)*100)/((float)totalexpneedtoupgrade), currentgamegainedexp);
		}
	}
	wsprintfW2(D2ScreenHook[1].wszMsg, temp_s);
}

void InitExp(){
	currentgameexp = D2GetUnitStat(PLAYER, STAT_EXP, 0);
	UpdateExp();
}

void __declspec(naked) UpdateExp_ASM()
{
		__asm {
		cmp [tShowExp.isOn],0
		je org
		call UpdateExp
org:
		pop edi
		pop esi
		pop ebp
		pop ebx
		ret 
	}
}

void InitScreenHook() {
	for (int i=0 ;i<10 ;i++){
		D2ScreenHook[i].show = 0 ;
	}

	if ( tShowExp.value==2 ){
		D2ScreenHook[0].show = &tShowExp.isOn ;
		D2ScreenHook[0].xpos = 120;
		D2ScreenHook[0].ypos = -65;
		D2ScreenHook[0].color = 0;
	}

	D2ScreenHook[1].show = &tShowExp.isOn ;
	D2ScreenHook[1].xpos = 120;
	D2ScreenHook[1].ypos = -50;
	D2ScreenHook[1].color = 0;

	D2ScreenHook[2].show = &tShowPing.isOn ;
	D2ScreenHook[2].xpos = -70;
	D2ScreenHook[2].ypos = -30;
	D2ScreenHook[3].color = 2;

	D2ScreenHook[3].show = &tShowPing.isOn ;
	D2ScreenHook[3].xpos = 65;
	D2ScreenHook[3].ypos = -30;
	D2ScreenHook[3].color = 2;
}

void DrawClientPatch() {
	
	if ( tShowPing.isOn ){
		if (PING >= 700)
			D2ScreenHook[2].color = 1;
		else
			D2ScreenHook[2].color = 2;
		wsprintfW2(D2ScreenHook[2].wszMsg, "%d",PING);
		D2ScreenHook[3].color = 2;
		wsprintfW2(D2ScreenHook[3].wszMsg, "%d",FPS);
	}

	for (int i=0 ;i<10 ;i++){
		if ( D2ScreenHook[i].show && *( D2ScreenHook[i].show )  ){
			int xpos = D2ScreenHook[i].xpos ;
			int ypos = D2ScreenHook[i].ypos ;
			if( xpos<0 ) xpos = xpos+SCREENSIZE.x;
			if( ypos<0 ) ypos = ypos+SCREENSIZE.y;
			D2DrawText( D2ScreenHook[i].wszMsg, xpos, ypos, D2ScreenHook[i].color, 0 );
		}
	}
	
	#include "m_DrawFunc.h"

}

void __declspec(naked) DrawClientPatch_ASM()
{
	__asm {
		call D2DrawClient;
		push ebx
		call DrawClientPatch
		pop ebx
		ret;
	}
}


#endif