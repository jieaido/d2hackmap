#ifdef FUNCTION_DECLARE
#define MODULE_MINIMAPPOINT
	void AddMinimapCell( DrlgLevel* pDrlgLevel , short cellno ,short xpos , short ypos );
	void ResetMiniCells();
	void BuildMiniMapPoint( DWORD dwAct );
	void DrawMinimapPoint();
#endif

#ifdef VARIABLE_DEFINE
	
	GVAR (BYTE,			nMinimapSize,					    1)
	GVAR (BYTE,			nMinimapCellCol,			       12)
	GVAR2(ToggleVar,	tMinimap,				1,	0,	 -1,	1, "Minimap Pointer " )
#endif

#ifdef PATH_INSTALL


#endif

#ifdef CONFIG_LOAD
	{6, "MinimapCells",             0			},
    {1, "MinimapToggle",            &tMinimap			},
    {2, "MinimapCellColour",        &nMinimapCellCol,   1}, 
    {2, "MinimapSize",              &nMinimapSize,      1},

#endif

#ifdef RUN_ONCE

	ResetMiniCells();
#endif

#ifdef RUN_LOOP


#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE
	if ( nMinimapSize>10 ) nMinimapSize = 10 ;

#endif