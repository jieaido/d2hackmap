#include "stdafx.h"

#include "d2ptrs.h"

#define PATH_INSTALL
#include "Module.h"
#undef PATH_INSTALL

#define PATH_INSTALL2
#include "Module.h"
#undef PATH_INSTALL2

static POINT lastCursorPoint;
static POINT lastPoint;

BOOL RelocD2Ptrs()
{
	DWORD *pPtrsStart = (DWORD *)&vD2StartOfPtr;
	DWORD *pPtrsEnd = (DWORD *)&vD2EndOfPtr;
	vD2ERR = 1;//防止这个值被优化
	DWORD *p = pPtrsStart, ret = TRUE;
	while (++p < pPtrsEnd){
		if (!(*p = GetDllOffset(*p))) ret = FALSE;
	};
	return ret;
}


BOOL InstallD2Patchs(Patch_t* pPatchStart, Patch_t* pPatchEnd)
{
  Patch_t* p = pPatchStart;
  while( p<pPatchEnd ){
    if ( !p->fInit){
      p->addr = GetDllOffset(p->addr);
      p->fInit = 1 ;
    }
    if (p->func && *(p->fEnable)){
      p->oldcode = new BYTE[p->len];
      ReadLocalBYTES(p->addr, p->oldcode, p->len);
      p->func(p->addr, p->param, p->len);
    }
    p++;
  }
  return TRUE;
}

void RemoveD2Patchs(Patch_t* pPatchStart, Patch_t* pPatchEnd)
{
  Patch_t* p = pPatchStart;
  while( p<pPatchEnd) {
    if (p->oldcode && *(p->fEnable) ){
      WriteLocalBYTES(p->addr, p->oldcode, p->len);
      delete p->oldcode;
    }
    p++;
  }
}

//D2loader 存在bug，部分dll需要迟后加装

BOOL fInstallPatch2 = 0;
BOOL RelocD2Ptrs2()
{
	DWORD *pPtrsStart = (DWORD *)&vD2StartOfPtr2;
	DWORD *pPtrsEnd = (DWORD *)&vD2EndOfPtr2;
	DWORD *p = pPtrsStart, ret = TRUE;
	while (++p < pPtrsEnd){
		if (!(*p = GetDllOffset(*p))) ret = FALSE;
	};
	return ret;
}
void InstallPatchAfterLoad(){
	if ( !fInstallPatch2 ){
		RelocD2Ptrs2();
		InstallD2Patchs(aD2Patch2s, aD2Patch2s+_ARRAYSIZE(aD2Patch2s));
		fInstallPatch2 = 1;
	}
}
void __declspec(naked) InstallPatchAfterLoad_ASM()
{
	__asm{
		cmp [fInstallPatch2],1
		je org
		push edi
		call InstallPatchAfterLoad
		pop edi
org:
		pop ecx
		lea eax, dword ptr [esp+0x4]
		push eax
		jmp ecx
	}
}

BOOL InstallPatchs(){
  if(!InstallD2Patchs(aD2Patchs, aD2Patchs+_ARRAYSIZE(aD2Patchs))){
    return FALSE;
  };

  #ifdef MODULE_GAMEWINDOW
	KeepWindowPatch();
  #endif

  return TRUE;
}

void RemovePatchs(){
	RemoveD2Patchs(aD2Patchs, aD2Patchs+_ARRAYSIZE(aD2Patchs));
	if ( fInstallPatch2 ){
		RemoveD2Patchs(aD2Patch2s, aD2Patch2s+_ARRAYSIZE(aD2Patch2s));
		fInstallPatch2 = 0;
	}
	#ifdef MODULE_GAMEWINDOW
		RemoveKeepWindowPatch();
	#endif

}

void InitCellFiles()
{
	char filename[MAX_PATH];
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < NUMOF_SHRINES; j++) {
			sprintf(filename,"%s%s%.2d.BMP",szPluginPath,"MINISHRINE"+(i?0:4) ,j);
			apMyShrineCells[i][j] = InitCellFile(LoadBmpCellFile(filename));
		}
	}

	sprintf(filename,"%s%s",szPluginPath,"WAYPOINT.BMP");
	pWaypointCell = InitCellFile(LoadBmpCellFile(filename));
	sprintf(filename,"%s%s",szPluginPath,"BLOBCELL.BMP");
	pMinimapObjectCell = InitCellFile(LoadBmpCellFile(filename));
	if(!pMinimapObjectCell) {
		sprintf(filename,"%s%s",szPluginPath,"BLOBDOT.BMP");
		pMinimapObjectCell = InitCellFile(LoadBmpCellFile(filename));
	}

	
	for (int i = 0; i < _ARRAYSIZE(pUnitBlobCells); i++) {
		if ( i<11 ){
			if (aszUnitBlobFiles[i]) {
				sprintf(filename,"%s%s.BMP",szPluginPath, aszUnitBlobFiles[i]);
				pUnitBlobCells[i] = InitCellFile(LoadBmpCellFile(filename));
			}
		}else{
			if (aszItemBlobFiles[i-11]) {
				sprintf(filename,"%s%s.BMP",szPluginPath, aszItemBlobFiles[i-11]);
				pUnitBlobCells[i] = InitCellFile(LoadBmpCellFile(filename));
			}
		}
	}
	if (aszUnitBlobFiles[11]) 
	{
		sprintf(filename,"%s%s.BMP",szPluginPath, aszUnitBlobFiles[11]);
		pMousePosCell = InitCellFile(LoadBmpCellFile(filename));
	}	

}

void DeleteCellFiles()
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < NUMOF_SHRINES; j++) {
			DeleteCellFile(apMyShrineCells[i][j]);
		}
	}

	DeleteCellFile(pWaypointCell);
	DeleteCellFile(pMinimapObjectCell);

	DeleteCellFile(pMousePosCell);

	memset( apMyShrineCells ,			0 ,			sizeof(apMyShrineCells) );
	pWaypointCell = NULL;
	pMinimapObjectCell = NULL;

	pMousePosCell = NULL;

	for (int i = 0; i < _ARRAYSIZE(pUnitBlobCells); i++) {
		DeleteCellFile(pUnitBlobCells[i]);
	}
	memset( pUnitBlobCells ,			0 ,			sizeof(pUnitBlobCells) );
}


BOOL Install(){

	//重定位函数
	if(!RelocD2Ptrs()){
		return FALSE;
	}

	//加载配置文件
	if(!LoadConfig()){
		return FALSE;
	}

#ifdef  MODULE_HIGHRESOLUTION
	if (MapSetResolution.XSize <640 || MapSetResolution.YSize < 480){
		MapSetResolution.XSize = 640;
		MapSetResolution.YSize = 480;
	}
#endif
		
	//加载旁路点
	if(!InstallPatchs()){
		return FALSE;
	}
	
#ifdef  MODULE_HIGHRESOLUTION
	InstallHRFPatch();
	//HighResolutionFix();
	//InitCellFiles();
#endif

	if (fAutomapPartyDefault != (BYTE)-1) D2SetAutomapParty(fAutomapPartyDefault==0?0:1);
	if (fAutomapNamesDefault != (BYTE)-1) D2SetAutomapNames(fAutomapNamesDefault==0?0:1);
	
	return TRUE;

}


void Uninstall(){
	
	#ifdef MODULE_AUTOMAPCELL
		//RemoveMyAutomapCells();
	#endif
	
	DestroyWindow (D2EventHwnd);
	DeleteCellFiles();
	RemovePatchs();
}

void ReloadConfig(){
	DeleteCellFiles();
	if (LoadConfig()){
		InitCellFiles();
		#ifdef MODULE_MINIMAPPOINT
		BuildMiniMapPoint(5);
		#endif

		ShowGameMessage("Config Reload Successful");
		ShowWarningMessage();
	}
}



static HWND parentHwnd;
static HWND childHwnd[10];
static bool sendsub;

void addChildHwnd(HWND subHwnd){
	if(D2EventHwnd == subHwnd){
		return;
	}
	bool flag = false;
	int n = 0 ;
	for(int i= 0 ;i<10;i++){
		if(childHwnd[i] == NULL ){
			n = i;
			break;
		}
	}
	for(int i= 0 ;i<10;i++){
		if(childHwnd[i] !=NULL && childHwnd[i] == subHwnd){
			flag = true;
			break;
		}
	}
	if(!flag){
		childHwnd[n] = subHwnd;
	}
}


void clearChildHwnd(){
	for(int i= 0 ;i<10;i++){
		childHwnd[i] = NULL;
	}
}

void SendChildMSG(UINT msg,WPARAM wparam , LPARAM lparam){
	//printMsg("send child msg");
	for(int i= 0 ;i<10;i++){
		if(childHwnd[i]!=NULL){
			//printMsg(" no null post");
			PostMessage(childHwnd[i], 
				msg, 
			wparam,  
			lparam); 
		}
	}
	 
}

static bool move_start;

static long lastlevel;
static long lastX;
static long lastY;
static DWORD lastunitid;
static DWORD lastunittype;


void setLastPostion(){
	if(isInDoor()){
		//Sleep(500);
		//UnitAny* unit  = GetNearDoor();
		SendChildMSG(WM_D2_SEND_INDOOR,lastunitid,0);  
	}
	
	lastX = PLAYER->pMonPath->wPosX;
	lastY = PLAYER->pMonPath->wPosY;
	lastlevel = LEVELNO;
	if(PLAYER->pMonPath->dwTargetId !=NULL && PLAYER->pMonPath->dwTargetType== UNITNO_ROOMTILE){
		lastunitid = PLAYER->pMonPath->dwTargetId;
		lastunittype =  UNITNO_ROOMTILE;
	}
}
bool isInDoor(){
	//TODO 判断是否是进出 洞口 , 传送门
	long diffx = PLAYER->pMonPath->wPosX - lastX;
	long diffy = PLAYER->pMonPath->wPosY - lastY;
	//printMsg("LEVELNO = %d , lastlevel = %d diffx = %d  diffy = %d " ,LEVELNO,lastlevel, diffx,diffy);

	if(lastlevel != LEVELNO && (  diffx >10 || diffx <-10 || diffy >10 || diffy <-10 ) ){
		//printMsg(" in a door ");

		return true;
		
	}
	return false;
}



UnitAny* GetNearDoor(){
	DrlgRoom1 * room = PLAYER->pMonPath->pRoom1;
	DrlgRoom2 * room2 = room->pRoom2;
	UnitAny * unit = room->pUnitFirst; 
	RoomTile * tile = room2->pRoomTiles; 
	HWND hwnd = D2GetHwnd(); 
	UnitAny * lastunit;
	long lastdis = -1;
	long lastx ;
	long lasty;
	while (unit!=NULL){
		 if(unit->dwUnitType == UNITNO_ROOMTILE){
			long x = (long)room->dwPosGameX + unit->pMonPath->wPosX   -(long)PLAYER->pMonPath->wPosX  ;
			long y = (long)room->dwPosGameY +  unit->pMonPath->wPosY   -(long)PLAYER->pMonPath->wPosY ;
			if(lastdis <0){
				lastunit = unit ;
				lastdis =  x*x + y*y;
				lastx = x;
				lasty = y;
			}else{
				if(lastdis > (x*x + y*y)){
					lastunit = unit;
				}
			}
		 }
		unit = unit->pListNext;
	}
	return lastunit; 
}

void InDoor(DWORD unitid ){
	/*BYTE pack1[9] = {0x13};			
	*(DWORD*)&pack1[1] = UNITNO_ROOMTILE;
	*(DWORD*)&pack1[5] = unitid;
	D2SendPacket(sizeof(pack1), 0, pack1);	
	printMsg(" end send ");*/ 
	DrlgRoom1 * room = PLAYER->pMonPath->pRoom1;
	UnitAny * unit = room->pUnitFirst;  
	HWND hwnd = D2GetHwnd(); 
	//long lastx ;
	//long lasty;
	while (unit!=NULL){
		if(unit->dwUnitId == unitid && unit->dwUnitType == UNITNO_ROOMTILE){
			BYTE pack1[9] = {0x13};			
			*(DWORD*)&pack1[1] = UNITNO_ROOMTILE;
			*(DWORD*)&pack1[5] = unitid;
			D2SendPacket(sizeof(pack1), 0, pack1);	
			//printMsg(" end send ");
			break;
		 }
		unit = unit->pListNext;
	} 
}


void printMsg(char* txt , ... ){
	wchar_t wbuf[512];
	va_list va;
	va_start(va, txt);
	int len = wvsprintf((char *)wbuf, txt, va);
	for (int i = len; i >= 0; i--) {
		wbuf[i] = ((char *)wbuf)[i];
	}
	D2ShowGameMessage( wbuf, 0);
	va_end(va);
}

 void writeMsg(char* msg,...){
	 va_list va;
	 va_start(va, msg);
	 char* file = "d:\\d2.log";
	 FILE *fp = fopen(file, "ab+");
	 char result[512];  
	 strcpy(result,msg	);
	 strcat(result,"\r\n"); 
	 vfprintf(fp,result,va);
	 fclose(fp);
 }
  void writeMsg1(char* msg,...){
	 va_list va;
	 va_start(va, msg);
	 char* file = "d:\\d2.log";
	 FILE *fp = fopen(file, "ab+");
	 vfprintf(fp,msg,va);
	 fclose(fp);
 }

 

HWND D2EventHwnd; 
 
int PASCAL D2WinMain() 
{ 
	HINSTANCE hinst = GetModuleHandle(NULL);
	HWND hwnd = D2GetHwnd();
	LONG_PTR  WndProc = GetWindowLongPtr(hwnd,GWLP_WNDPROC);
    MSG msg;
    BOOL bRet; 
    WNDCLASS wc; 
    //UNREFERENCED_PARAMETER(lpszCmdLine); 
 
    // Register the window class for the main window. 
 

    wc.style = 0; 
    wc.lpfnWndProc = (WNDPROC) WndProc; 
    wc.cbClsExtra = 0; 
    wc.cbWndExtra = 0; 
    wc.hInstance = hinst; 
	
    wc.hIcon = LoadIcon((HINSTANCE) NULL, 
        IDI_APPLICATION); 
    //wc.hCursor = LoadCursor((HINSTANCE) NULL, 
    //    IDC_ARROW);  
	//wc.lpszMenuName =  "MainMenu"; 
    wc.lpszClassName = D2WINCLASS; 
    RegisterClass(&wc);

    D2EventHwnd = CreateWindow(D2WINCLASS, D2EVENTWIN_TITLE, 
        WS_CAPTION, CW_USEDEFAULT, CW_USEDEFAULT, 
        CW_USEDEFAULT, CW_USEDEFAULT, (HWND) NULL, 
        (HMENU) NULL, (HINSTANCE)NULL, (LPVOID) NULL); 
	
	if(D2EventHwnd==NULL){
		//printMsg(" create  window error : %d" , GetLastError());
	}

    ShowWindow(D2EventHwnd, 0); 
    UpdateWindow(D2EventHwnd); 
	SetWindowText(D2EventHwnd,D2EVENTWIN_TITLE);
	//printMsg(" create  window  success " );
    while( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
    { 
        if (bRet == -1)
        {
            // handle the error and possibly exit
        }
        else
        { 
			if(fInGame){
				if(msg.message == WM_D2_SEND_PARENT_HWND){
					//printMsg(" get parent");
					//printMsg(" send back");
					//printMsg("lParam =%x , wParam= %x",msg.lParam,msg.wParam);
					//收到消息后 , 设置parentHwnd 
					parentHwnd = (HWND)msg.wParam;
					//发回消息 ,告知主窗口 ,子窗口的Hwnd
					PostMessage(parentHwnd,WM_D2_SEND_CHILD_HWND,(WPARAM)D2EventHwnd,0);
					clearChildHwnd();
				}else if(msg.message == WM_D2_SEND_CHILD_HWND){
					//printMsg(" set  child ");
					//printMsg("lParam =%x , wParam= %x",msg.lParam,msg.wParam);
					//增加子窗口的HWND
					addChildHwnd((HWND)msg.wParam);
				}else if(msg.message == WM_D2_SEND_LBDOWN){
					//printMsg(" left  down ");
					//ClickPoint(msg.wParam,msg.lParam);
				}else if(msg.message == WM_D2_SEND_LBUP){ 
					//printMsg(" left  up ");
					//ClickPoint(msg.wParam,msg.lParam);
				}else if(msg.message == WM_D2_SEND_LBMOVE){ 
					//printMsg(" left  moving ");
					MoveToPoint(msg.wParam,msg.lParam);
				}else if(msg.message == WM_D2_SEND_MOVE){
				
				}else if(msg.message == WM_D2_SEND_INDOOR){
					InDoor(msg.wParam);
				}

			}else{
				//TranslateMessage(&msg); 
				//DispatchMessage(&msg); 
			}
        }
    } 
 
    // Return the exit code to the system. 
 
    return msg.wParam; 
} 
static bool clicking;
static bool whiling ;
void MoveToPoint(WPARAM wparam , LPARAM lparam){
	if(!tAutoRunToggle.isOn){
		return;
	}
	HWND hwnd = D2GetHwnd();
	POINT p;
	p.x = (long)wparam;
	p.y = (long)lparam;

	long xdiff ,ydiff;
	xdiff =   p.x  - (long)PLAYER->pMonPath->wPosX*10;
	ydiff =  p.y - (long)PLAYER->pMonPath->wPosY *10;
	POINT cursorPoint ;
	int whilecount;
	whilecount = 0; 
	while ( whilecount <5 &&  (xdiff >MIN_DIS || xdiff <-MIN_DIS || ydiff >MIN_DIS || ydiff <-MIN_DIS )){
		if(!tAutoRunToggle.isOn  ){
			whiling = false;
			return;
		} 
		if(xdiff>800 || ydiff >600 || ydiff <-600 || xdiff <-800){
			return ;
		}
		cursorPoint.x = xdiff +400;
		cursorPoint.y = ydiff + 300; 
		SendMessage(hwnd ,WM_LBUTTONDOWN, 0,MAKELPARAM(cursorPoint.x,cursorPoint.y));
		SendMessage(hwnd ,WM_MOUSEMOVE, MK_LBUTTON,MAKELPARAM(cursorPoint.x,cursorPoint.y));
		Sleep(10);
		SendMessage(hwnd ,WM_LBUTTONUP, MK_LBUTTON,MAKELPARAM(cursorPoint.x,cursorPoint.y));
		xdiff =   p.x  - (long)PLAYER->pMonPath->wPosX*10;
		ydiff =  p.y - (long)PLAYER->pMonPath->wPosY*10 ;
		whilecount = whilecount+1;
	} 
}



void ClickPoint(WPARAM wparam , LPARAM lparam){
	

}