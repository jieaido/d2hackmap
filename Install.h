#ifndef INSTALL_H
#define INSTALL_H

BOOL Install();
void Uninstall();
BOOL LoadConfig();
void ReloadConfig();
void ShowWarningMessage();
BOOL InstallD2Patchs(Patch_t* pPatchStart, Patch_t* pPatchEnd);
void RemoveD2Patchs(Patch_t* pPatchStart, Patch_t* pPatchEnd);
void InstallPatchAfterLoad_ASM();
void InitCellFiles();
void DeleteCellFiles();
void printMsg(char*  txt,... );

void CALLBACK HandleWinEvent(HWINEVENTHOOK hook, DWORD event, HWND hwnd, 
                             LONG idObject, LONG idChild, 
                             DWORD dwEventThread, DWORD dwmsEventTime); 
LRESULT WINAPI  MyMouseProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI  MyMouseProc1(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI  MyMouseProc2(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI  D2Proc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI  DDEProc(int nCode, WPARAM wParam, LPARAM lParam);
void writeMsg(char* msg,...);
void writeMsg1(char* msg,...);
void addChildHwnd(HWND subHwnd);
int PASCAL D2WinMain(); 
void SendChildMSG(UINT msg,WPARAM wparam , LPARAM lparam);
void MoveToPoint(WPARAM wparam , LPARAM lparam);
void ClickPoint(WPARAM wparam , LPARAM lparam);
void clearChildHwnd();
bool isInDoor();
UnitAny* GetNearDoor();
void setLastPostion(); 
void InDoor(DWORD unitid);
static long test_x ;
static long test_y ; 
static bool shift_down;

//static HHOOK hhook; 
//static HHOOK hhook1;

extern HMODULE hInstDLL;

#define SHAKE_X (*p_D2MapShakeX)
#define SHAKE_Y (*p_D2MapShakeY)

extern  long OLD_SHAKE_X;
extern  long OLD_SHAKE_Y;
#define REVISE_X  1
#define REVISE_Y  -221
#define MIN_DIS 50
#define CLICK_RANGE 10

extern HWND D2EventHwnd;


static double pi = 3.1415926535;  
static double R37 = 37 * pi / 180;
static POINT LeftClickPoint ;
static bool leftdown;

#define WM_D2_SEND_PARENT_HWND WM_APP
#define WM_D2_SEND_CHILD_HWND WM_APP+1
#define WM_D2_SEND_LBDOWN WM_APP+2
#define WM_D2_SEND_LBUP WM_APP+3
#define WM_D2_SEND_LBMOVE WM_APP+4
#define WM_D2_SEND_MOVE WM_APP+5
#define WM_D2_SEND_INDOOR WM_APP+6




#define D2EVENTWIN_TITLE  "PAYALLMONEY_D2EVENT"
#define D2WINCLASS  "D2MainWndClass"



#endif

