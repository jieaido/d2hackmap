#ifndef CONFIGSTRUCT_H
#define CONFIGSTRUCT_H

	//命令结构
    struct ToggleVar {
        BYTE  type ;    // 1  按键切换开关(可触发事件)  2 按键触发事件，不带参数 3或0  按键触发事件 带参数 
        BYTE  isOn;	    //是否开启
        BYTE  key;	    //触发按键
        BYTE  value;	//命令值
        char* desc;     //事件描述
        union{
            void *func; //调用的函数
            void (*funcVoid)();
            void (*funcParam)(int);
        };
        int param;     //func2函数参数
		BOOL  isLoad;  //是否在配置中加载的
    };

    //配置文件参数
	/*
	1  按键触发事件
	2  数值 长度可为 1  2  4  
	3  字符串 单字节
	4  字符串 双字节,带颜色
	5  数组
	6  特殊1
	7  特殊2
	*/

    struct ConfigVar {
        int		type ;			//配置类型
        char	*szCmdName;	    //命令名
        void	*pVar;			//保存命令的对象
        BYTE	size;			//对象值的长度,这里用int会有问题
        short	anArrayMax[4];	//对应数组的各维长度
    };

    //用来建立VCB文件树
    struct TreeNode {
        char   *key;
        char   *str;
        TreeNode *left, *right;
    };
    
    //旁路点结构
    struct Patch_t{
        void (*func)(DWORD, DWORD, DWORD);
        DWORD addr;
        DWORD param;
        DWORD len;
        BOOL *fEnable;
        BYTE *oldcode;
        BOOL fInit ;

    };

	//地图指向配置文件
	struct MinimapConfig{
		int  nPoints  ;		//指向数量
		struct {
			WORD wPointNo ;	//指向编号
			BYTE fFlag;		//是否生效
			BYTE nColour;	//颜色
		} aPoint[30];
	};
	
	//可指向的地图块
	struct MinimapCell{
		short	cellno;
		short	xpos;
		short	ypos;
	};

	//指向目标
	struct MinimapPoint{
		int  nPoints  ;		//指向数量
		struct {
			short	xpos;
			short	ypos;
			BYTE	nColour;	//颜色
		} aPoint[30];
	};
	
	struct D2ScreenHookStruct
	{
		BYTE *show;
		int xpos;
		int ypos;
		wchar_t wszMsg[512];
		BYTE color;
	};

	struct InventoryType {
		BYTE invType;
		short left;
		short bottom;
		BYTE nGridXs;
		BYTE nGridYs;
		BYTE nGridWidth;
		BYTE nGridHeight;
	};
	
	struct BugQuestInfo{
		DWORD nQuestNo; //任务编号
		DWORD nStatus ; //任务状态
		DWORD nType ;   //保护模式
		BYTE *fEnable ; //是否开始
		char szMsg[10]; //名称
	} ;

	struct MonTC
	{
		WORD wGroup;
		WORD wLevel;
		int nTc;
		int nRtc;
		BOOL fInit;	
	};
	
	struct ViewUnitInfo {
		DWORD dwUiNo;
		DWORD dwUnitId;
		DWORD dwUnitType;
		UnitAny *pUnit;
	};

	struct PlayerStat {
		DWORD dwStatNo;
		char* szDesc;
		char* szSuffix;
	};

	struct LevelInfo{
		DrlgLevel* pDrlgLevel;
		BOOL fReady;
		BOOL fRevealed;
	};

	struct StatMonitor {
		wchar_t wszDesc[2][30];
		DWORD	dwStatNo;
		DWORD	dwTimer;
		DWORD   dwColor;
		BOOL	fEnable;
	};
	
	struct MyTimer {
		DWORD dwValue;
		DWORD dwTimer;
		BOOL  fEnable;
	};

	struct ScrollDis {
	double dis;
	double maxdis;
	double todis;
	double newx;
	double newy;
	double newdis;
	double R;
};

#endif