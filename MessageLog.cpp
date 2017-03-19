#include "stdafx.h"

#ifdef MODULE_MESSAGELOG



void __fastcall LogMessage(wchar_t* wstr)
{
	char asc_buf[0x400];
	wchar_t buf[0x400];
	wchar_t *p = buf;

	// strip the D2 color code
	for (wchar_t *pw = wstr;*pw; ++pw) {
		if (*pw == 0xFF)
		{
			pw+=2;
			continue;
		}
		else {
			*p++ = *pw;
		}
	}
	*p++ = '\r';
	*p++ = '\n';
	*p = '\0';
	
	if (wcslen(buf) == 2)
	{
		// blank message , I just enter a game, log the game name and password.
		GameStructInfo *gi = GAMEINFO;
		if(!gi)return;
		if(gi->szGameName[0]) {
			if (gi->szGamePassword[0])
				wsprintfW2(buf,"---%s(*%s) enter game[%s] %s/%s---\r\n",gi->szCharName,gi->szAccountName,gi->szRealmName,gi->szGameName,gi->szGamePassword);
			else
				wsprintfW2(buf,"---%s(*%s) enter game[%s] %s---\r\n",gi->szCharName,gi->szAccountName,gi->szRealmName,gi->szGameName);
		}
	}
	else if ( tLogMessage.value==2 ) return;
	// convert to UTF-8 string
//	WChar2MChar(buf,asc_buf,wcslen(buf));
	WideCharToMultiByte(CP_UTF8,NULL,buf,-1,asc_buf,0x400,NULL,NULL);

	SYSTEMTIME t;
	char timebuf[256];
	GetLocalTime(&t);
	sprintf(timebuf,"[%04X][%04d-%02d-%02d %02d:%02d:%02d]",GetCurrentProcessId(),t.wYear,t.wMonth,t.wDay,t.wHour, t.wMinute, t.wSecond );

	HANDLE hFile = OpenFileWrite("d2messages.log");
	if (hFile != INVALID_HANDLE_VALUE){
		if (GetFileSize(hFile,NULL)/1024 > dwMessageFileSize){
			CloseHandle(hFile);
			__try{
				char newname[256];
				sprintf(newname,"d2messages%04d%02d%02d.log",t.wYear,t.wMonth,t.wDay);
				rename("d2messages.log",newname);
				hFile = OpenFileNew("d2messages.log");
				if ( hFile == INVALID_HANDLE_VALUE ) return ;
			}__except(EXCEPTION_EXECUTE_HANDLER) {
				return;
			}
		}
		SetFilePointer(hFile, 0, 0, FILE_END);
		WriteFile(hFile,timebuf,strlen(timebuf));
		WriteFile(hFile,asc_buf,strlen(asc_buf));
		CloseHandle(hFile);
	}
 }

void __declspec(naked) MessageLogPatch1_ASM()
{
	__asm {
		cmp [tLogMessage.isOn],0
		je oldcode
		mov     ecx, [esp+0x2C]
		pushad
		call LogMessage
		popad
oldcode:
		mov	edx,[p_D2ScreenSizeX]
		mov edx, [edx]
		ret
	}
}

void __declspec(naked) MessageLogPatch2_ASM()
{
	__asm {
		cmp [tLogMessage.isOn],0
		je oldcode
		pushad
		call LogMessage
		popad
oldcode:
		add eax, 0x2710
		ret
	}
}


void LogExitMessage()
{
	if (tLogMessage.isOn==0) return;
	GameStructInfo *gi = GAMEINFO;
	if(!gi)return;

	char asc_buf[0x400];
	char asc_buf1[0x400];
	
	// I just exit a game, log it.
	
	sprintf(asc_buf,"---%s(*%s) exit game---\r\n",gi->szCharName,gi->szAccountName);

	SYSTEMTIME t;
	char timebuf[256];
	GetLocalTime(&t);
	HANDLE hFile = OpenFileWrite("d2messages.log");
	if ( hFile == INVALID_HANDLE_VALUE ) return ;
	sprintf(timebuf,"[%04X][%04d-%02d-%02d %02d:%02d:%02d]",GetCurrentProcessId(),t.wYear,t.wMonth,t.wDay,t.wHour, t.wMinute, t.wSecond);

	SetFilePointer(hFile, 0, 0, FILE_END);

	if (tShowExp.isOn){
		int exp = D2GetUnitStat(PLAYER, STAT_EXP, 0);
		sprintf(asc_buf1,"---EXP gained[%d]---\r\n",exp - currentgameexp);

		WriteFile(hFile,timebuf,strlen(timebuf));
		WriteFile(hFile,asc_buf1,strlen(asc_buf1));
	}
	WriteFile(hFile,timebuf,strlen(timebuf));
	WriteFile(hFile,asc_buf,strlen(asc_buf));
	CloseHandle(hFile);
}


#endif