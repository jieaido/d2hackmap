#include "stdafx.h"
//÷ª≤‚ ‘”√
//6FB8BC30 + 12*n 
#ifdef MODULE_PACKETHANDLER


void __fastcall GamePacketReceivedIntercept(BYTE* aPacket, DWORD aLength)
{
	/*if( tPacketHandler.isOn ){
		if (  aPacket[0] == 0xA7 ){
		wchar_t wszTemp[512];
		wcscpy(wszTemp,L" [");
		for ( int i=0 ; i<12 ; i++){
			wsprintfW(wszTemp+wcslen(wszTemp),L" %X" , aPacket[i]);
		}
		wcscat(wszTemp,L" ]");
		D2ShowGameMessage (wszTemp,0);
		}
		
	}*/
	//printMsg("receive [0] == %x , 1 = %x , 2 = %x , 3 = %x ",aPacket[0],aPacket[1],aPacket[2],aPacket[3]);
	if (  aPacket[0] == 0x9c ){
		printMsg("aPacket = %x", aPacket );
		WORD* id = (WORD*) &aPacket[3];
		ItemTxt* txt = D2GetItemTxt(aPacket[4]);
		BYTE* txt1 = (BYTE*)txt;
		ItemTxt* txt2 =  D2GetItemTxt(aPacket[4]+0x200);
		/*printMsg("item dwCode  = %d", txt->dwCode );
		printMsg("item dwCost  = %d", txt->dwCost );
		printMsg("item nType  = %d", txt->nType );*/
		printMsg("dwCode=%d,dwCost=%d,nType=%d,nLevelReq=%d,nSocket=%d,",txt2->dwCode,txt2->dwCost,txt2->nType,txt2->nLevelReq,txt2->nSocket);
		//writeMsg1("dwCode=%d,dwCost=%d,nType=%d,nLevelReq=%d,nSocket=%d,",txt2->dwCode,txt2->dwCost,txt2->nType,txt2->nLevelReq,txt2->nSocket);
		
		wchar_t wszTemp[512];
		wcscpy(wszTemp,L" [");
		for ( int i=0 ; i<40 ; i++){
			wsprintfW(wszTemp+wcslen(wszTemp),L"%X " , aPacket[i]);
			writeMsg1("%d\t" , aPacket[i]);
		}
		writeMsg1(" \r\n" );
		wcscat(wszTemp,L" ]");
		D2ShowGameMessage (wszTemp,0); 
	}
	return;
}
//////////////////////////////////////////////////////////////////////
// GamePacketReceivedSTUB()
// -------------------------------------------------------------------

// before call orignal code
// bl = packet number
// esi = length
// edi = pointer to packet
// free register before pushad: eax
//////////////////////////////////////////////////////////////////////
void __declspec(naked) GamePacketReceivedInterceptPatch_ASM()
{
	__asm {
		mov eax, esi; // save length

		// original code
		movzx esi, bl;
		mov ebp, esi
		shl ebp, 1
		add ebp, esi
		pushad;
		// Call our clean c function
		mov edx, eax;
		mov ecx, edi;
		call GamePacketReceivedIntercept;
		// Return to game
		popad;
		add dword ptr[esp], 1; 
		ret;
	}
}



#endif