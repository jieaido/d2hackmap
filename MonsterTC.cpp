#include "stdafx.h"

#ifdef MODULE_MONSTERLIFEBAR

/*
TC 计算

struct TreasureClassItem {
	DWORD _1[2];		//+00
	DWORD dwIdx;		//+08
	union {
		DWORD dwProp;
		struct {
			DWORD _3:2;
			DWORD fTc:1;
		};				//+0C
	};
};

struct TreasureClass {			//size = 0x2C
	WORD wGroup;				//+00
	WORD wLevel;				//+02
	DWORD dwItems;				//+04
	DWORD _1[8];				//+08
	TreasureClassItem *pItems;	//+28
};


在第一次进游戏时，对所有TC值计算对应的TC等级(取其子项的最大等级),TreasureClass最多1012个
TreasureClassEx.txt中，从第一行有效数据起从1开始编号，再加上160，即为游戏中的TC结构索引
游戏内索引1-160为基础TC，其所有子项都指向一个itemtype(bow，weap，mele，armo，abow),按32个一组拆分,

每个TreasureClass的子项TreasureClassItem可以指向TreasureClass，最终递归指向具体的itemtype
当指向itemtype时， dwIdx为gptItemTables的索引,否则为一个TC索引

TreasureClass的group属性第一次进游戏时为0或者实际group+5，以后每进一个新的房间+5  ;

tc 从3开始以3递增，实际最大87 
runeTC  每2个rune 一组，共17组， 33独占一组


TC提升规则
如果mlvl>tc->level 且 tc->group 不为0 , 将tc提升到同group中level不小于mlvl的tc项
*/


static MonTC anMonsterTCs[1014];
static BOOL fIsTcInit = FALSE ; 	

void CalculateHighestTC(int tcno , WORD offset)
{
	TreasureClass *pTc = D2GetTreasureClasses(tcno, 0);
	if(!pTc)return;

	anMonsterTCs[tcno].wLevel = pTc->wLevel;
	anMonsterTCs[tcno].wGroup = ( ( pTc->wGroup==0 ) ? 0 : pTc->wGroup-offset );
	anMonsterTCs[tcno].fInit = false;

	for (int i = 0; i < (int)pTc->dwItemNums; i++) {

		DWORD dwThingNo = pTc->pItems[i].dwThingNo;

		if (pTc->pItems[i].fTc) {
			if ( dwThingNo<= 160) {
				int groupno = (dwThingNo-1)/32;
				int tc = (((dwThingNo-1)%32)+1)*3;
				if (groupno==1 && tc>anMonsterTCs[tcno].nTc ) anMonsterTCs[tcno].nTc=tc;
			} else {
				if ( anMonsterTCs[ dwThingNo ].fInit==false ){
					CalculateHighestTC(dwThingNo , offset);
				}
				if ( anMonsterTCs[dwThingNo].nTc > anMonsterTCs[tcno].nTc ){
					anMonsterTCs[tcno].nTc = anMonsterTCs[dwThingNo].nTc;
				}
				if ( anMonsterTCs[dwThingNo].nRtc > anMonsterTCs[tcno].nRtc ){
					anMonsterTCs[tcno].nRtc = anMonsterTCs[dwThingNo].nRtc;
				}

			}
		} else {
			ItemTxt *itemtxt = D2GetItemTxt(dwThingNo);
			if (itemtxt && itemtxt->nType == 74) {
				int runeno = (itemtxt->szCode[1]-'0')*10+(itemtxt->szCode[2]-'0');
				int runetc = (int)(runeno/2)+runeno%2;
				if (runetc >anMonsterTCs[tcno].nRtc) anMonsterTCs[tcno].nRtc = runetc;
			}
		}
	}
	anMonsterTCs[tcno].fInit = true;
}

void InitTCList()
{	
	if(fIsTcInit) return ;
	memset( anMonsterTCs ,		0 ,			sizeof(anMonsterTCs) );
	int i;
	WORD offset;
	TreasureClass *pTc=D2GetTreasureClasses(262, 0) ;
	offset= pTc->wGroup - 2;//获得修正值; 262 为Act 1 Melee A   group 为2
	
	for (i = 1; i <1014; i++)
	{
		CalculateHighestTC(i ,offset );
	}
	fIsTcInit = true;
}


MonTC *GetTcLevel(WORD tcno , DWORD mlvl) {
	
	int tcidx = tcno;
	if (anMonsterTCs[tcidx].wGroup>0 && mlvl>(DWORD)anMonsterTCs[tcidx].wLevel) {
		WORD tempgroup = anMonsterTCs[tcidx].wGroup ;
		while ( anMonsterTCs[tcidx+1].wGroup == tempgroup){
			tcidx++;
			if ( mlvl<=(DWORD)anMonsterTCs[tcidx].wLevel )break;

		}
	}
	return &anMonsterTCs[tcidx];
}




#endif