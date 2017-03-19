
#ifdef PATH_INSTALL
static Patch_t aD2Patchs[] = {
	

#endif

#ifdef PATH_INSTALL2
	static Patch_t aD2Patch2s[] = {
#endif

#ifdef CONFIG_LOAD

static ConfigVar aConfigVars[] = {
	{0,     "JustInHere",    (void*)-1     , 0 , {0,0,0,0}  },

#endif


#ifdef VARIABLE_DEFINE

#ifndef GVARDEF
    #define GVARDEF

	#define GVAR(d1,v1,v2) extern d1 v1 ;
    #define GVAR2(d1,v1,...) extern d1 v1 ;
#else
	#define GVAR(d1,v1,v2) d1 v1 = v2 ;
    #define GVAR2(d1,v1,...) d1 v1 = { __VA_ARGS__ } ;

#endif
 
#endif
