#include "stdafx.h"
#include <Psapi.h>
#pragma comment(lib,"Psapi.lib")

#ifdef MODULE_ITEMDEFINE

//物品定义相关

int GetItemIndex(int pos)
{
	return (pos < *p_D2WeaponsTxts) ? pos :((pos -= *p_D2WeaponsTxts) < *p_D2ArmorTxts) ? pos+1000 : pos - *p_D2ArmorTxts + 2000;
}

BYTE GetItemColour(UnitAny *pItem,DWORD arridx) {
	ItemTxt *pItemTxt = D2GetItemTxt( pItem->dwTxtFileNo );

	if ( pItemTxt->nType==4 ) {//gold
		return (D2GetUnitStat(pItem, STAT_GOLD, 0) >= (int)dwGoldGoodNum) ? anGoldGoodCol[arridx] : anGoldPoorCol[arridx];
	}

	if ( pItemTxt->nType == 74) {//rune
		DWORD dwRuneNo = (pItemTxt->szCode[1]-'0')*10+(pItemTxt->szCode[2]-'0')-1;
		if ( dwRuneNo < 100 ) return anRuneColours[dwRuneNo][arridx];
	}

	int index = GetItemIndex(pItem->dwTxtFileNo);
	if ( index >2999 ) index= 2999;

	DWORD dwQuality = (pItem->pItemData->dwQuality-1)&7;
	if ( arridx>0 && ItemHaveLevel( pItemTxt->nType)){
		BYTE nHiddenLevel = anItemHideLevel[index][dwQuality];//小于隐藏等级的隐藏
		if (nHiddenLevel!=(BYTE)-1 && ( pItem->pItemData->dwItemLevel < (DWORD)(nHiddenLevel>99?0:nHiddenLevel) )  ) return (BYTE)-2;
	}
	int socknum = D2GetUnitStat(pItem, STAT_NUMSOCKETS, 0);
	if( socknum > 6) socknum = 6;
	char color = anItemColours[index][dwQuality][!!D2CheckItemFlag(pItem, ITEMFLAG_ETHEREAL, 0, "?")][socknum][arridx];
	return (BYTE)color;
}


void SwitchItemMode(){
	DWORD lastmode = nItemShowMode;
	nItemShowMode = (++nItemShowMode)%4 ;
	if(nItemShowMode==0)nItemShowMode=1;
	wchar_t temp[512];
	wsprintfW(temp, L"<Hackmap>: Switch to Item Show Mode  %d to %d",lastmode, nItemShowMode);
	D2ShowPartyMessage(temp, 0);
}

void MouseScrollMapSwitch(){
	DWORD lastmode = nMouseScrollMap;
	nMouseScrollMap = (++nMouseScrollMap)%3 ;
	if(nMouseScrollMap==0)nMouseScrollMap=1;
	SHAKE_X = 0 ;
	SHAKE_Y = 0 ;
	wchar_t temp[512];
	wsprintfW(temp, L"<Hackmap>: Switch Mouse Scroll Mode  %d to %d",lastmode, nMouseScrollMap);
	D2ShowPartyMessage(temp, 0);
}

//struct thread_data
//{
// int m_id;
// thread_data(int id) : m_id(id) {}
//};
//DWORD WINAPI thread_func(LPVOID lpParameter)
//{
// thread_data *td = (thread_data*)lpParameter;
// HWND hwnd = D2GetHwnd();
// Sleep(1000);
// long ret = PostMessage(hwnd, // broadcasts message 
//	WM_KEYDOWN, // initiates conversation 
//	0x1000, // handle to client DDE window 
//	0x1000); 
//	printMsg(" ret  = %d " , ret);
//	if(ret == NULL ){
//		printMsg(" error  = %d " , GetLastError());
//	}
// return 0;
//}

char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0) { // All spaces?
    return str;
  }

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator
  *(end) = 0;

  return str;
}

static HWND findwins[10];
static int findidx;
BOOL CALLBACK FindD2Window(
  _In_ HWND   chwnd,
  _In_ LPARAM lParam
){
	HWND hwnd = D2GetHwnd();
	char* parentExe = (char*)lParam;
	char filename[512];
	getHwndExe(chwnd,filename);
	HINSTANCE  chinstance = (HINSTANCE)GetWindowLongPtr(chwnd,GWLP_HINSTANCE);
	char className[50];
	GetClassName(chwnd,className,50);
	if(chwnd != D2EventHwnd && lstrcmpi((char*)lParam, filename) ==0 && lstrcmpi(className, D2WINCLASS) ==0){ 
		//printMsg(" send WM_D2_SEND_PARENT_HWND  findidx == %d", findidx++);
		PostMessage(chwnd, // broadcasts message 
				WM_D2_SEND_PARENT_HWND, // initiates conversation 
			(WPARAM)D2EventHwnd, // handle to client DDE window 
			0);
	}
	return true;
}

void SendD2Message(){
	//给所有暗黑窗口发送消息 HWND_BROADCAST 无效
	//
	
	SendParentHwnd();
}

void SendD2MessageToWindow(HWND to , UINT msg ,  WPARAM wParam, LPARAM lParam){
	PostMessage(to, msg , wParam,  lParam); 
}

void SendParentHwnd(){
	//给所有暗黑窗口发送消息 , 有返回的记录下来 , 作为子窗口 , 没有返回的记录下来
	HWND hwnd = D2GetHwnd();
	char exepath[512];
	getHwndExe(hwnd,exepath); 
	findidx = 0;
	EnumWindows(FindD2Window,(LPARAM)exepath);
	//for(int i =0 ;i <=findidx;i++){
	//	HWND findhwnd = findwins[i];
	//	PostMessage(findhwnd, // broadcasts message 
	//			WM_D2_SEND_PARENT_HWND, // initiates conversation 
	//		(WPARAM)D2EventHwnd, // handle to client DDE window 
	//		0);

	//}
}
void getHwndExe(HWND hwnd , char* filename){
	DWORD pid  ;
	GetWindowThreadProcessId(hwnd , &pid);
	HANDLE  h = OpenProcess(PROCESS_QUERY_INFORMATION |
                            PROCESS_VM_READ,false,pid);
	GetModuleFileNameEx(h,NULL,filename,  512);  
}


#endif