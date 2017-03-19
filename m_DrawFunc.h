//所有需要一直显示的屏幕信息，在这里添加显示函数

DrawCenterAlertMsg();

#ifdef MODULE_GAMECOUNT
	ShowGameCount();
#endif

#ifdef MODULE_GAMEMONITOR
	DrawMonitorInfo();
#endif
