#include "stdafx.h"
bool doubleon;
void RunToSwitch(){
	DWORD lastmode = nRunTo;
	nRunTo = (++nRunTo)%20 ;
	if(nRunTo==0)nRunTo=1;
	wchar_t temp[512];
	wsprintfW(temp, L"<Hackmap>: Switch to Item Show Mode  %d to %d",lastmode, nItemShowMode);
	D2ShowPartyMessage(temp, 0);
}
void RunToToggle(){
	ClickPoint();

}
void InitPoints(){
	
}
static int time = 0;
DWORD WINAPI click_thread_func(LPVOID lpParameter)
{
	/*POINT p;
	int i = 0 ; 
	HWND hwnd = D2GetHwnd();

	while (RunPoints[0][0][i][0]!=0){
		p.x = RunPoints[0][0][i][0];
		p.y = RunPoints[0][0][i][1];
		SendMessage(hwnd ,WM_LBUTTONDOWN, 0,MAKELPARAM(p.x,p.y));
		Sleep(350);
		SendMessage(hwnd ,WM_LBUTTONUP, MK_LBUTTON,MAKELPARAM(p.x,p.y));
		i++;
	}*/
	
	return 0;
}
bool inrange(long x , long x1){
	long dif = x-x1;
	dif = dif>0 ? dif :-dif; 
	return dif<=5;
}
static bool startmove =false;
static long lastx ,lasty;
void moving(long x , long y ){
	HWND hwnd = D2GetHwnd();
	
	if(!startmove){
		SendMessage(hwnd ,WM_LBUTTONDOWN, 0,MAKELPARAM(x,y));
		startmove = true;
	}else{
		if(lastx == x && lasty == y ){
			SendMessage(hwnd ,WM_MOUSEMOVE, MK_LBUTTON,MAKELPARAM(x,y));
		}else{
			SendMessage(hwnd ,WM_LBUTTONUP, MK_LBUTTON,MAKELPARAM(lastx,lasty));
			Sleep(100+rand() % 200);
			SendMessage(hwnd ,WM_LBUTTONDOWN, 0,MAKELPARAM(x,y));
		}
	}
	lastx = x ;
	lasty = y ; 
	long rate = rand() % 200;
	Sleep(100+rate);
}
void endmoving(long x , long y ){
	HWND hwnd = D2GetHwnd();
	SendMessage(hwnd ,WM_LBUTTONUP, MK_LBUTTON,MAKELPARAM(x,y));
	startmove= false;
}
DWORD WINAPI move_thread_func(LPVOID lpParameter)
{
//	int* idx = (int*) lpParameter;
//	long targetx = RelativePoints[*idx][0]  , targety=RelativePoints[*idx][1];
//	long startx = PLAYER->pMonPath->wPosX;
//	long starty = PLAYER->pMonPath->wPosY;
//	long endx = startx + targetx;
//	long endy = starty + targety ;
//	long ratex = targetx>0 ?1:-1;
//	long ratey = targety>0 ?1:-1;
//
////	POINT p;
//	int i = 0 ; 
//	HWND hwnd = D2GetHwnd();
//	long x , y  ;
//	long rate ;
//	bool xin = inrange(PLAYER->pMonPath->wPosX,endx);
//	bool yin = inrange(PLAYER->pMonPath->wPosY,endy);
//	rate = rand() % 100;
//	bool firstx = false;
//	bool firsty = false;
//	bool firsto = false;
//	long xrand , yrand;
//	while ( !xin || !yin  ){ 
//		
//		if(xin){
//			if(!firstx){
//				xrand = rand() % 10 * (rand() % 10>5?1:-1);
//				yrand = rand() % 10 * (rand() % 10>5?1:-1);
//				rate = rand() % 100;
//				firstx = true;
//			}
//			x = 400 -ratey*(100+rate) + xrand;
//			y = 300 +ratey *(100+rate)/4*3 + yrand; 
//			moving(x,y);
//		}else if(yin){
//			if(!firsty){
//				xrand = rand() % 10 * (rand() % 10>5?1:-1);
//				yrand = rand() % 10 * (rand() % 10>5?1:-1);
//				rate = rand() % 100;
//				firsty = true;
//			}
//			x = 400 +ratex*(100+rate) + xrand;
//			y = 300 +ratex *(100+rate)/4*3 + yrand;
//			moving(x,y);
//		}else{ 
//			if(!firsto){
//				xrand = rand() % 10 * (rand() % 10>5?1:-1);
//				yrand = rand() % 10 * (rand() % 10>5?1:-1);
//				rate = rand() % 100;
//				firsto = true;
//			}
//			x = 400 + xrand;
//			y = 300 +ratex*(100+rate)/4*3;
//			moving(x,y);
//		}
//		xin = inrange(PLAYER->pMonPath->wPosX,endx);
//		yin = inrange(PLAYER->pMonPath->wPosY,endy);
//		ratex = (endx - PLAYER->pMonPath->wPosX ) >0?1:-1;
//		ratey = (endy - PLAYER->pMonPath->wPosY)  >0?1:-1;
//	}
//	endmoving(x,y);
	
	return 0;
}



void ClickPoint(){
	//printMsg("%x,%x,%x,%x",anRunPoints[0][0][0][0],anRunPoints[0][0][0][1],anRunPoints[0][0][0][2],anRunPoints[0][0][0][3]);
	int type = 0; 
	CreateThread(NULL, 0, move_thread_func, &type, 0, 0);	
	//PLAYER->pRoomNext
	
}
void GoToPoint(){
	CreateThread(NULL, 0, move_thread_func, NULL, 0, 0);	
}

void RunTo( DWORD mode){ 
	nRunTo =  mode ; 
}

void __declspec(naked) LButtonDownPatch_ASM()
{
	__asm {
		pushad
		call LButtonDownPatch
		popad
		mov     eax, 0x6FBCC2B8
		ret
	}
}



void __fastcall LButtonDownPatch()
{	
	//if(fInGame){
	//	//输出鼠标点击位置
	//	POINT p;

	//	HWND hwnd = D2GetHwnd();
	//	//先计算出鼠标相对位置
	//	GetCursorPos(&p);
	//	ScreenToClient(hwnd, &p);
	//	long x = PLAYER->pMonPath->wPosX*10+p.x-400;
	//	long y = PLAYER->pMonPath->wPosY*10+p.y-300;
	//	//printMsg(" point %d,%d,%d,%d ",p.x,p.y ,PLAYER->pMonPath->wOffsetX,PLAYER->pMonPath->wOffsetY);
	//	//printMsg(" point %x,%x,%x,%x ",p.x,p.y ,PLAYER->pMonPath->wOffsetX,PLAYER->pMonPath->wOffsetY); 
	//	//writeMsg(" 0x%x,0x%x,0x%x,0x%x, ",p.x,p.y ,PLAYER->pMonPath->wPosX,PLAYER->pMonPath->wPosY);
	//}
}

void StartShake(){
	if(fPlayerInTown || !tMouseScrollMapToggle.isOn) return;
	if (nMouseScrollMap ==2 && PLAYER->pSkill->pRightSkill->pSkillInfo->wSkillId == 54){
		doubleon = true;
		ShakeWhenMoving();
	}
}

void ShakeWhenMoving(){
	if(fPlayerInTown || !tMouseScrollMapToggle.isOn) return;
	HWND hwnd = D2GetHwnd();  
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hwnd, &pt);
	
	if (nMouseScrollMap ==2 && PLAYER->pSkill->pRightSkill->pSkillInfo->wSkillId == 54 && doubleon){
		pt.x = pt.x - 400;
		pt.y = pt.y - 300;
		float rate = nMouseScrollRate;
		rate = rate /10;
		SHAKE_X =pt.x *rate;
		SHAKE_Y =pt.y *rate;
	}
}

void StopShake(){
	if(doubleon){
		doubleon = false;
		SHAKE_X = 0 ;
		SHAKE_Y = 0;
	} 
}

void __declspec(naked) RButtonDownPatch_ASM()
{
	__asm {
		pushad
		call RButtonDownPatch
		popad 
		mov     eax, 0x6FBCC3E0
		ret
	}
}



void __fastcall RButtonDownPatch()
{
	//printMsg(" right down " );
	if(fInGame){
		StartShake();
		if(!fPlayerInTown){
			//如果是野蛮人,那么停止攻击
			//printMsg(" stat == %s " ,sMonitorStr[55]);
			for ( int i = 0 ; i < 200 ; i ++ ){	 
				if(sMonitorStr[i].dwStatNo == 55 &&  sMonitorStr[i].fEnable == 1 && PLAYER->pSkill->pRightSkill->pSkillInfo->wSkillId == 151){
					//TODO 这里禁止攻击
					//printMsg("cancel attack");
					//fPlayerInTown = 1;
					HWND	hwnd = D2GetHwnd();
					POINT p;
					//先计算出鼠标相对位置
					GetCursorPos(&p);
					//SendMessage(hwnd, WM_RBUTTONUP, NULL, NULL);
					SendMessage(hwnd, WM_RBUTTONUP, NULL, MAKELONG(400, 300));
					SendMessage(hwnd, WM_LBUTTONDOWN, NULL, MAKELONG(400, 300));
					SendMessage(hwnd, WM_LBUTTONUP, NULL, MAKELONG(400, 300));

					//PLAYER->pSkill->pRightSkill->dwMode = 0;
					break;
				}
			}
		}
	}
	
}



void __declspec(naked) LDownMouseMovingPatch_ASM()
{
	__asm { 
		
		pushad
		call LDownMouseMovingPatch
		popad
		mov    eax, p_D2MovingVariable	
		mov    eax, [eax]	
		ret
	}
}

void __fastcall LDownMouseMovingPatch()
{
	if(fInGame){
		ShakeWhenMoving();
	}
	//printMsg("moving ...");
	//writeMsg(" aaa=%x");

}


void __declspec(naked) TestPatch_ASM()
{
	__asm { 
		//mov     ecx, p_D2TestVariable
		//push    offset dword_6FA0A0D8
		pushad
		call TestPatch
		popad 
		mov    eax, p_D2TestVariable	
		mov   eax , [eax]  
		// mov     eax, dword_6FA09F14
		
		
		ret
	}
}

void __fastcall TestPatch()
{

		writeMsg("  in game ?? ");

}
