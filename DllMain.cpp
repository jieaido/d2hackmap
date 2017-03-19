// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

HMODULE hInstDLL=NULL;
char szPluginPath[MAX_PATH]="\0";

void ReleaseMem(){
	#ifdef MODULE_ITEMEXTINFO
		UnLoadExtInfo();
	#endif

}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		hInstDLL = hModule;
		DisableThreadLibraryCalls(hInstDLL);
		GetModuleFileName( hInstDLL, szPluginPath, MAX_PATH );
		*(strrchr( szPluginPath, '\\' ) + 1)='\0';
		return Install();
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		ReleaseMem();
		if (!lpReserved)
			Uninstall();
		break;
	}
	return TRUE;
}


#define D2LOADER_PLUGIN

#ifdef D2LOADER_PLUGIN

extern "C" PVOID __stdcall QueryInterface() //NOTE :- needs to be exported
{
	char filename[MAX_PATH];
	GetModuleFileName(hInstDLL, filename, MAX_PATH);
	LoadLibrary(filename);
	return NULL;
}


#endif