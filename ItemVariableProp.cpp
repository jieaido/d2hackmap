#include "stdafx.h"


#ifdef MODULE_ITEMVARIABLEPROP

//变量范围显示
/*

第一次运行时，先初始化所有绿色，暗金，神符之语的属性表
对于某些变量，需要根据类型拆分属性

short aItemPropInfo[3][500][30][4];
第一位 0 暗金 1 绿色 2 神符之语
第二位 各类型对应编号 set 128个 unique 397个  runeword 169个
第三位 装备属性  共359个属性 , 只保存可变的
第三位 0 记录statno值 1 记录param值 2 记录最小值 3 记录最大值
(3*500*20*4*4)/1024 = 469K ;


对于被击中触发技能，攻击时触发技能，gethit触发技能3类属性，如果等级可变，算法比较麻烦，直接if else维护了

*/
/*
TEST
wchar_t wszTemp[512];
wsprintfW(wszTemp, L"[%d] [%d] [%d] [%d]" , mPropId ,  pItemProp[i].Param , pItemProp[i].MinVal,pItemProp[i].MaxVal);
D2ShowGameMessage(wszTemp,0);

*/


static int aItemPropInfo[3][500][20][4];
static int nStatCount = 0 ;

void SetPropInfo( int itemType , int index ,int propMax , ItemProp *pItemProp){

	if (!pItemProp)return;
	int nCount = 0 ;
	int (*pStat)[4] = &aItemPropInfo[itemType][index][0];

	for ( int i=0 ; i<propMax ; i++){//1

		int mPropId = pItemProp[i].PropId ;

		if ( mPropId>=0 && pItemProp[i].MinVal!= pItemProp[i].MaxVal ){//2

			PropertiesTxt *pPropertiesTxt = D2GetPropertiesTxt( mPropId );
			if ( !pPropertiesTxt ) continue;

			short *pStatNo = pPropertiesTxt->wStatNo;
			
			if ( mPropId==267 && pPropertiesTxt->nFunc[0]==36 ){
				continue;
			}
			//特殊属性拆分
			
			if ( pPropertiesTxt->nFunc[0]==21 ){
				//加角色技能
				pStat[nCount][0] = 83;
				pStat[nCount][1] = pPropertiesTxt->wVal[0];
				pStat[nCount][2] = pItemProp[i].MinVal ;
				pStat[nCount][3] = pItemProp[i].MaxVal ;
				nCount++;
				continue;
			}

			if ( mPropId == 29 ){
				//增强伤害
				pStat[nCount][0] = 17;
				pStat[nCount][1] = pItemProp[i].Param;
				pStat[nCount][2] = pItemProp[i].MinVal;
				pStat[nCount][3] = pItemProp[i].MaxVal;
				nCount++;
				pStat[nCount][0] = 18;
				pStat[nCount][1] = pItemProp[i].Param;
				pStat[nCount][2] = pItemProp[i].MinVal;
				pStat[nCount][3] = pItemProp[i].MaxVal;
				nCount++;
				continue;
			}
			//个别属性，删除
			if ( mPropId>=134 && mPropId<=140)continue;  //单独增加伤害上下限
			if ( mPropId==248 )continue;  //冰火电上下限伤害

			if ( mPropId <= 128 &&  mPropId >=126){
				//被打击时，被击中时，攻击时触发技能

				if (pItemProp[i].MaxVal==0){

					int statno = -1 ;
					int min = -1 ;
					int max = -1;

					if ( mPropId == 126 ){
						if ( index==254 ) {
							statno = 195;
							min = 16;
							max = 20;
						}else if ( index==259 ) {
							statno = 195;
							min = 14;
							max = 20;
						}
					}
					if ( mPropId == 127 ){
						if ( index==136 ) {
							statno = 198;
							min = 13;
							max = 20;
						}
					}

					if ( mPropId == 128 ){
						if ( index==264 ) {
							statno = -1; //因为掉落要求太高，这个实际变成了不可变
							min = 20;
							max = 20;
						}else if ( index==270 ) {
							statno = 201;
							min = 13;
							max = 19;
						}else if ( index==245 ) {
							statno = 201;
							min = 7;
							max = 19;
						}else if ( index==137 ) {
							statno = 201;
							min = 12;
							max = 20;
						}
					}
					if ( statno>=0 ){
						pStat[nCount][0] = statno;
						pStat[nCount][1] = pItemProp[i].Param ;
						pStat[nCount][2] = min ;
						pStat[nCount][3] = max ;
						nCount++;
					}

				}
				continue;
			}
				
			for( int j=0 ; j< 7; j++ ){//3  子属性拆分
		
				if ( pStatNo[j]>=0 ){//4

					pStat[nCount][0] = pStatNo[j];
					pStat[nCount][1] = pItemProp[i].Param;
					pStat[nCount][2] = pItemProp[i].MinVal ;
					pStat[nCount][3] = pItemProp[i].MaxVal ;
					
					nCount++;
				}//4

			}//3

		}//2
	}//1
	
	if ( nCount> nStatCount) nStatCount = nCount;

}

wchar_t *GetStatRange( wchar_t *wszStr , DWORD dwStatId , DWORD wParam = 0) {

	
	static BOOL fItemStatInit = FALSE;

	if ( fItemStatInit == FALSE ){

		memset(aItemPropInfo,	-1	,	sizeof(aItemPropInfo));
		nStatCount = 0 ;
		
		//暗金
		for ( int i =0  ; i < 500 ; i++ ){
			UniqueItemTxt *pUniqueTxt = D2GetUniqueItemTxt(i);
			if (!pUniqueTxt)break;
			SetPropInfo( 0 , i , 12 , pUniqueTxt->Prop );
		}
		
		//绿色
		for ( int i =0  ; i < 200 ; i++ ){
			SetItemTxt *pSetTxt = D2GetSetItemTxt(i);
			if (!pSetTxt)break;
			SetPropInfo( 1 , i , 9 , pSetTxt->Prop );
		}

		//神符之语
		for ( int i =0  ; i < 169 ; i++ ){
			RuneWordTxt *pRuneWordTxt = D2GetRuneWordTxt(i);
			if (!pRuneWordTxt)break;
			SetPropInfo( 2 , i , 7 ,pRuneWordTxt->Prop );
		}
		fItemStatInit = TRUE;
	}
	
	UnitAny *pUnit = VIEWITEMUNIT ;
	if (pUnit){
		
		DWORD dwQuality = pUnit->pItemData->dwQuality;
		int idx = -1;
		int fileindex = -1 ;
		if ( dwQuality==ITEM_QUALITY_UNIQUE ) {
			idx = 0 ;
			fileindex = D2GetItemFileIndex(pUnit);
		}else if (  dwQuality==ITEM_QUALITY_SET ){
			idx = 1 ;
			fileindex = D2GetItemFileIndex(pUnit);
		}else if ( D2CheckItemFlag(pUnit, ITEMFLAG_RUNEWORD, 0, "?") ){
			idx = 2 ;
			fileindex = D2GetRuneWordTxtIndex( pUnit->pItemData->wMagicPrefix[0] );
		}

		if ( idx>=0 && fileindex>=0 ){

			int (*pStat)[4] = &aItemPropInfo[idx][fileindex][0];
			for ( int i=0 ; i<nStatCount ; i++){

				if ( pStat[i][0]<0 ) break;
				if ( pStat[i][0]==dwStatId &&  pStat[i][1]==wParam ){
					

					if (dwStatId==194){
						ItemTxt *pItemTxt = D2GetItemTxt(pUnit->dwTxtFileNo);
						if ( pStat[i][3] > (pItemTxt->nSocket)){
							pStat[i][3] = (pItemTxt->nSocket);
						}
					}

					if ( dwStatId==216 ){
						int lvl = D2GetUnitStat(PLAYER, STAT_LEVEL, 0);
						wsprintfW(wszStr+wcslen(wszStr), L" \xFF\x63\x34(%d-%d)\xFF\x63\x33",pStat[i][2]*lvl/8 , pStat[i][3]*lvl/8 );
					}else{
						int extvalue = 0 ;
						if(idx==2){
							/*对于神符之语，将符文的属性也加到变量范围内*/
							UnitAny *pItem = D2GetFirstItemInInv(pUnit->pInventory);
							while (pItem) {
								extvalue = extvalue + D2GetUnitStat(pItem,dwStatId,0);
								pItem = D2GetNextItemInInv(pItem);
							}
						}
						wsprintfW(wszStr+wcslen(wszStr), L" \xFF\x63\x34(%d-%d)\xFF\x63\x33",pStat[i][2]+extvalue , pStat[i][3]+extvalue);
					}
					break;
				}

			}

		}
		
	}
	return wszStr;
}


DWORD __fastcall GetItemPropStringPatch( wchar_t *wszStr , StatEx * pStatEx ,DWORD flag){

	if ( tShowItemVariableProp.isOn && !flag ){
		//ShowGameMessage(pStatEx->wParam);

		DWORD dwStatId = pStatEx->wStatId;
		DWORD dwParam = pStatEx->wParam ;

		switch( dwStatId ){
			case 195:
			case 198:
			case 201:
				dwParam = dwParam>>6;
				break;
			case 188:
				{
					int chartype = dwParam/8;
					int skilltab = dwParam%8;
					dwParam = chartype*3+skilltab;
				}
				break;
			default:
				break;
		}
		GetStatRange( wszStr , dwStatId , dwParam );
	}
	return pStatEx->wStatId;

}

void __declspec(naked) GetItemPropStringPatch_ASM()
{
	// esp +4 +8*ebp+2D4 = pStatEx
	// ebx = dwStatNo
	// esi = wszPropStr
	__asm {
		lea edx , [esp+4+8*ebp+0x2D4]
		mov ecx , esi
		push [esp+0x10]
		call GetItemPropStringPatch
//org , eax from ebx
		sub eax, 0x17
		ret
	}
}

void __fastcall StrcatItemPropStringPatch( wchar_t *wszMainStr  , wchar_t *wszPropStr ,DWORD dwStatNo ){
	
	int len = wcslen(wszPropStr);
	if ( len == 0 ) return;
	wszPropStr [ len-1] = L'\0';//去掉回车
	if ( tShowItemVariableProp.isOn 
		#ifdef MODULE_ITEMDESC 
			&& tViewSocketBase.isOn == 0 
		#endif

	){
		
		GetStatRange( wszPropStr , dwStatNo );
	}
	wcscat( wszMainStr , wszPropStr );
	wcscat( wszMainStr , L"\n");

}

void __declspec(naked) StrcatItemPropStringPatch_ASM()
{
	__asm {
		push [esp+0xC]
		call StrcatItemPropStringPatch
		ret
	}
}

wchar_t * __fastcall StrcatSocketStringPatch( wchar_t *wszStr ){
	
	//拼孔数字符串的地方,下一步代码拼接回车

	if ( tShowItemVariableProp.isOn ){
		GetStatRange( wszStr , 194 );
	}
	return wszStr;
}

void __declspec(naked) StrcatSocketStringPatch_ASM()
{
	__asm {
		push edi

		mov ecx , eax
		call StrcatSocketStringPatch

		pop edi

		mov edx, dword ptr [esp+0x14]
		mov ecx, eax
		ret
	}
}


wchar_t * __fastcall StrcatDefenseStringPatch( wchar_t *wszStr ){
	
	//拼防御字符串的地方,下一步代码拼接回车
	//对于ETH物品 Bug打孔，如果bug出来比正常的非bug最大值还小，则认为是非bug
	if ( tShowItemVariableProp.isOn ){

		UnitAny *pUnit = VIEWITEMUNIT ;
		if (pUnit){

			ItemTxt *pItemTxt = D2GetItemTxt( pUnit->dwTxtFileNo );
			if( pItemTxt && pItemTxt->dwMinDef>0 ){

				int mDef = D2GetUnitBaseStat(pUnit, 31,0);
				int mMinDef = pItemTxt->dwMinDef;
				int mMaxDef = pItemTxt->dwMaxDef ;
				wchar_t wszPrep[256] = {L"\0"};
				wchar_t wszTemp[512] = {L"\0"};

				if ( D2CheckItemFlag(pUnit, ITEMFLAG_ETHEREAL, 0, "?") ){
					mMinDef = (int)(mMinDef * 1.5) ;
					mMaxDef = (int)(mMaxDef * 1.5) ;

					if ( mDef>mMaxDef && pUnit->pItemData->dwQuality==2 && D2CheckItemFlag(pUnit, ITEMFLAG_SOCKETED, 0, "?")  ){
						//普通物品 ,带孔，防御比最大防御还大，则为ETH BUG
						mMinDef = (int)(mMinDef * 1.5) ;
						mMaxDef = (int)(mMaxDef * 1.5) ;
						wcscpy(wszPrep , L"(Bug)");
					}

				}

				if ( mDef > mMaxDef ){//超过最大防御，说明天生带ED，防御自动max+1
					wsprintfW( wszTemp, L"%s(Min: %d, Max: %d, Now: %d+%d)\n" ,wszPrep, mMinDef , mMaxDef , mMaxDef ,mDef - mMaxDef );
				}else{
					wsprintfW( wszTemp, L"%s(Min: %d, Max: %d, Now: %d)\n" ,wszPrep, mMinDef , mMaxDef , mDef);
				}
				wcsrcat(wszStr,  wszTemp);
			}

		}

	}
	return wszStr;
}

void __declspec(naked) StrcatDefenseStringPatch_ASM()
{
	__asm {
		push ebx

		mov ecx , edi
		call StrcatDefenseStringPatch

		pop ebx

		mov edx, dword ptr [esp+0x1C]
		mov ecx, eax
		ret
	}
}


wchar_t * __fastcall StrcatDamageStringPatch( wchar_t *wszStr ){

	//拼攻击字符串，直接拼接(盾牌也会调用)
	if ( tShowItemVariableProp.isOn ){
		UnitAny *pUnit = VIEWITEMUNIT ;
		if (pUnit){

			ItemTxt *pItemTxt = D2GetItemTxt( pUnit->dwTxtFileNo );
			if( pItemTxt &&  (int)(pUnit->dwTxtFileNo)< *p_D2WeaponsTxts ){
				wchar_t wszTemp[512] = {L"\0"};
				int Sockets = pItemTxt->nSocket;
				if ( pUnit->pItemData->dwQuality<=3){
					int maxSockets = 0;
					int iLevel = pUnit->pItemData->dwItemLevel;
					ItemTypeTxt *pItemTypeTxt = D2GetItemTypeTxt(pItemTxt->nType);
					if ( iLevel<=25){
						maxSockets = pItemTypeTxt->nMaxSock1;
					}else if ( iLevel<=40 ){
						maxSockets = pItemTypeTxt->nMaxSock25;
					}else{
						maxSockets = pItemTypeTxt->nMaxSock40;
					}
					if (Sockets>maxSockets)Sockets = maxSockets;
					wsprintfW2Colour( wszTemp, 0,"(Range: %d, Speed: %d, Sockets: 1-%d)\n" ,pItemTxt->nRangeAdder+1, pItemTxt->dwSpeed , Sockets);
				}else{
					wsprintfW2Colour( wszTemp, 0,"(Range: %d, Speed: %d)\n" ,pItemTxt->nRangeAdder+1, pItemTxt->dwSpeed);
				}
				wcsrcat(wszStr,  wszTemp);
			}

		}

	}
	
	return wszStr;
}
//一般物品调用
void __declspec(naked) StrcatDamageStringPatch_ASM1()
{
	__asm {
		push ebx

		mov ecx , edi
		call StrcatDamageStringPatch

		pop ebx

		mov edx, eax
		lea ecx, dword ptr [esp+0x68]
		ret
	}
}
//绿色武器调用

void __declspec(naked) StrcatDamageStringPatch_ASM2()
{
	__asm {
		push ebp

		mov ecx , edi
		call StrcatDamageStringPatch

		pop ebp

		mov edx, eax
		lea ecx, dword ptr [esp+0x194C]
		ret
	}
}
#endif