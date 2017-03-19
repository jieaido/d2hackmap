#ifdef FUNCTION_DECLARE
#define MODULE_LOCKWINDOW
void UnlockWindow();
void LockWindow();
#endif

#ifdef VARIABLE_DEFINE
GVAR2(ToggleVar,	tLockWindowToggle,			1,	0,	-1,		1,	"Lock Window Toggle")
extern RECT rcOldClip;

#endif

#ifdef PATH_INSTALL


#endif

#ifdef CONFIG_LOAD
  {1, "LockWindowToggle",    &tLockWindowToggle       }, 

#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP

 LockWindow();

#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif