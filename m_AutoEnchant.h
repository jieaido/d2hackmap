#ifdef FUNCTION_DECLARE
	#define MODULE_AUTOENCHANT
	
	void AutoEnchant(UnitAny *pUnit);
#endif

#ifdef VARIABLE_DEFINE
GVAR2(ToggleVar,	tAutoEnchant,				1,	0,	-1,	 1,	"Auto Enchant")

 
#endif

#ifdef PATH_INSTALL


#endif

#ifdef CONFIG_LOAD
	{1, "AutoEnchantToggle",   &tAutoEnchant     },

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
