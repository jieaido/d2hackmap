// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once


#define _CRT_SECURE_NO_DEPRECATE        // 去除输入输出函数安全检查
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件:
#include <windows.h>
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include "HelpFunc.h"
#include "d2vars.h"
#include "d2structs.h"
#include "MyStructs.h"

#include "d2ptrs.h"
#include "d2callstub.h"
#include "d2helpfunc.h"

#define FUNCTION_DECLARE
#include "Module.h"
#undef FUNCTION_DECLARE


#define VARIABLE_DEFINE
#include "Module.h"
#undef VARIABLE_DEFINE


#include "Install.h"
#include "Define.h"

// TODO: 在此处引用程序需要的其他头文件


