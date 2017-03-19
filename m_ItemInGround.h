#ifdef FUNCTION_DECLARE
	#define MODULE_ITEMINGROUND
	BOOL  CheckItemVisible(UnitAny *pItem);
#endif

#ifdef VARIABLE_DEFINE

GVAR2(ToggleVar,	tShowIdentifiedItem,  1,	0,	-1,		1,	"Show Identified items")
GVAR2(ToggleVar,    tHiddenItems,         1,	1,	VK_ADD,	1,	"Show hidden items")
 
#endif

#ifdef PATH_INSTALL


#endif

#ifdef CONFIG_LOAD
  {1, "ShowIdentifiedItem",    &tShowIdentifiedItem	 },
  {1, "HiddenItemsToggle",     &tHiddenItems         },

#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP


#endif


#ifdef RUN_ENDGAME


#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
