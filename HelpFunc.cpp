#include "stdafx.h"

DWORD GetDllOffset(char *dll, int offset)
{
	HMODULE hmod = GetModuleHandle(dll);
	if (!hmod)
		hmod = LoadLibrary(dll);
	if (!hmod) return 0;
	if (offset < 0) {
		return (DWORD)GetProcAddress(hmod, (LPCSTR)-offset);
	}
	return ((DWORD)hmod)+offset;
}

DWORD GetDllOffset(int num)
{
	static char *dlls[] = {"D2CLIENT.DLL", "D2COMMON.DLL", "D2GFX.DLL", "D2WIN.DLL", "D2LANG.DLL", "D2CMP.DLL", "D2MULTI.DLL", "BNCLIENT.DLL", "D2NET.DLL", "STORM.DLL", "FOG.DLL", "D2GAME.DLL","D2LAUNCH.dll","D2MCPCLIENT.dll"};
	return GetDllOffset(dlls[num&0xff], num>>8);
}


DWORD VirtualProtect(DWORD pAddress, DWORD len, DWORD prot)
{
	DWORD oldprot = 0;
	VirtualProtect((void *)pAddress, len, prot, &oldprot);
	return oldprot;
}


void WriteLocalBYTES(DWORD pAddress, void *buf, int len)
{
	DWORD oldprot = VirtualProtect(pAddress, len, PAGE_EXECUTE_READWRITE);
	WriteProcessMemory(GetCurrentProcess(), (void *)pAddress, buf, len, 0);
	VirtualProtect(pAddress, len, oldprot);
}

void ReadLocalBYTES(DWORD pAddress, void *buf, int len)
{
	ReadProcessMemory(GetCurrentProcess(), (void *)pAddress, buf, len, 0);
}


void FillLocalBYTES(DWORD pAddress, BYTE ch, int len)
{
	BYTE *buf1 = new BYTE[len];
	memset(buf1, ch, len);
	WriteLocalBYTES(pAddress, buf1, len);
	delete buf1;
}

DWORD ReadLocalDWORD(DWORD pAddress)
{
	DWORD val = 0;
	ReadLocalBYTES(pAddress, &val, 4);
	return val;
}

void InterceptLocalCode2(BYTE inst, DWORD pOldCode, DWORD pNewCode, int len)
{
	BYTE *buf1 = new BYTE[len];
	buf1[0] = inst;
	*(DWORD *)(buf1+1) = pNewCode;
	memset(buf1+5, INST_NOP, len-5);
	WriteLocalBYTES(pOldCode, buf1, len);
	delete buf1;
}


void InterceptLocalCode(BYTE inst, DWORD pOldCode, DWORD pNewCode, int len)
{
	pNewCode -= (pOldCode+5);
	InterceptLocalCode2(inst, pOldCode, pNewCode, len);
}


void PatchCALL(DWORD addr, DWORD param, DWORD len)
{
	InterceptLocalCode(INST_CALL, addr, param, len);
}

void PatchJMP(DWORD addr, DWORD param, DWORD len)
{
	InterceptLocalCode(INST_JMP, addr, param, len);
}

void PatchFILL(DWORD addr, DWORD param, DWORD len)
{
	FillLocalBYTES(addr, (BYTE)param, len);
}

void PatchVALUE(DWORD addr, DWORD param, DWORD len)
{
	WriteLocalBYTES(addr, &param, len);
}


HANDLE OpenFileNew(char *filename)
{
	return CreateFile(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
}

HANDLE OpenFileRead(char *filename)
{
	return CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
}

HANDLE OpenFileWrite(char *filename)
{
	return CreateFile(filename, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
}

DWORD WriteFile(HANDLE hFile, void *buf, DWORD len)
{
	DWORD numdone = 0;
	WriteFile(hFile, buf, len, &numdone, NULL);
	return numdone;
}

DWORD ReadFile(HANDLE hFile, void *buf, DWORD len)
//NOTE :- validates len bytes of buf
{
	DWORD numdone = 0;
	ReadFile(hFile, buf, len, &numdone, NULL);
	return numdone;
}

BYTE *AllocReadFile(char *filename)
{
	HANDLE hFile = OpenFileRead(filename);
	int filesize = GetFileSize(hFile, 0);
	if (filesize <= 0) return 0;
	BYTE *buf = new BYTE[filesize];
	ReadFile(hFile, buf, filesize);
	CloseHandle(hFile);
	return buf;
}


char *ReadFileLine(char *str, int len, HANDLE hFile)
{
	char ch, *p = str;
	while (--len) {
		if (!ReadFile(hFile, &ch, 1)) break;
		if ((*p++ = ch) == '\n') break;
	}
	*p = 0;
	return str[0]?str:0;
}


void SwapInt(int &num1, int &num2)
{
	int temp = num1;
	num1 = num2;
	num2 = temp;
}

void *memcpy2(void *dest, const void *src, size_t count)
{
	return (char *)memcpy(dest, src, count)+count;
}

void wcscpy2(wchar_t *dest, char *src)
{
	do { *dest++ = *src; }while(*src++);
}

wchar_t * wcsrcat(wchar_t *dest, wchar_t *src)
{
	memmove(dest+wcslen(src), dest, (wcslen(dest)+1)*sizeof(wchar_t));
	memcpy(dest, src, wcslen(src)*sizeof(wchar_t));
	return dest;
}

wchar_t * wscolorcpy(wchar_t *dest, wchar_t *src , BYTE color)
{
	wcscpy( dest , src) ; 
    wchar_t *p = dest;	

	while(*p){
		p++;
	}
	if(*(p-1)==0xff){
		if(color!=(BYTE)-1){
			*p++ = 'c';
			*p++ = '0'+color;
			*p= 0;
		}else{
			*(p-1) = 0;
		}
	}
	return dest;
}

void trimspaces(char *str)
{
	char *p1 = str, *p2 = str+strlen(str);
	while (isspace(*p1)) p1++;
	do p2--; while ((p2 >= p1) && isspace(*p2));
	*++p2 = 0;
	memmove(str, p1, (p2+1-p1)*sizeof(char));
}

void trimspaces(wchar_t *str)
{
	wchar_t *p1 = str, *p2 = str+wcslen(str);
	while (iswspace(*p1)) p1++;
	do p2--; while ((p2 >= p1) && iswspace(*p2));
	*++p2 = 0;
	memmove(str, p1, (p2+1-p1)*sizeof(wchar_t));

}

char *DblToStr(double dblSour,int decimal,char *desc)
{
	int dec, sign;

	char *buffer;
	char *p=desc;
	buffer = _ecvt( dblSour, 10, &dec, &sign );

	if (dec>0)
	{
		for (int i=0;i<dec;i++)
		{
			*p++=*buffer++;
		}
	}
	else
	{
		p[0]='0';
		p++;
	}
	*p='.';
	p++;
	for(int j=0;j<decimal; j++){
		if(*buffer) *p++=*buffer++;
		else *p++='0';
	}
	*p='\0';
	return desc;
}



wchar_t * __cdecl wsprintfW2(wchar_t *dest, char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	int len = wvsprintf((char *)dest, fmt, va);
	for (int i = len; i >= 0; i--) {
		dest[i] = ((char *)dest)[i];
	}
	va_end(va);
	return dest;
}

char *AllocStrN(char *str, int len)
{
	if (len <= 0) return 0;
	char *newstr = new char[len+1];
	memcpy(newstr, str, len);
	newstr[len] = 0;
	return newstr;
}

wchar_t * __fastcall ColourD2String(wchar_t *str, DWORD col)
{
	memmove(str+3, str, (wcslen(str)+1)*sizeof(wchar_t));
	str[0] = 0xff;
	str[1] = 'c';
	str[2] = '0'+(int)col;
	return str;
}

wchar_t * __cdecl wsprintfW2Colour(wchar_t *dest, int col, char *fmt, ...)
{
	dest[0] = 0xff;
	dest[1] = 'c';
	dest[2] = '0'+(int)col;
	dest += 3;
	va_list va;
	va_start(va, fmt);
	int len = wvsprintf((char *)dest, fmt, va);
	for (int i = len; i >= 0; i--) {
		dest[i] = ((char *)dest)[i];
	}
	va_end(va);
	return dest;
}


void ConvertToColorString( BYTE *dst , char  *src , int size)
{
  char ch = 0, col = 0, next;
  BYTE *pOld = dst;
  int sizecount = 0 ;
  ch = *src++;
  sizecount++;
  while(ch){
    next = *src;
    if( ch=='%' && next){
      if ( isalpha(next) ){
        col = toupper(next)-'A'+10;
		if(col>12){
			col = 0;
			*dst++ = ch;
		}else{
			src++;
		}
      }else if (isdigit(next)){
        col = (char)strtol(src,&src,10);
	  }else{
	    col = 0;
	    *dst++ = ch;
	  }
      if ( col ){
        *dst++ = 0xff;
        *dst++ = 'c';
        *dst++ = '0'+col;
        pOld = dst;
      }
      
    }else{
      *dst++ = ch;
    }
	ch = *src++;
    sizecount++;

  }
  if(col){
	*dst++ = 0xff;
  }
  *dst = 0 ;
  if(sizecount>=size){
    *(pOld+size) = L'\0';
  }

}


void UnicodeFix2(LPWSTR lpText)
{
	if (lpText) {
		size_t LEN = wcslen(lpText);
		for (size_t i = 0; i < LEN; i++)
		{
			if (lpText[i] == 0xf8f5) // Unicode 'y'
				lpText[i] = 0xff; // Ansi 'y'
		}
	}
}

int MyMultiByteToWideChar(
						UINT CodePage,         // code page
						DWORD dwFlags,         // character-type options
						LPCSTR lpMultiByteStr, // string to map
						int cbMultiByte,       // number of bytes in string
						LPWSTR lpWideCharStr,  // wide-character buffer
						int cchWideChar        // size of buffer
						)
{
	int r = MultiByteToWideChar(CodePage, dwFlags, lpMultiByteStr, cbMultiByte, lpWideCharStr, cchWideChar);
	UnicodeFix2(lpWideCharStr);
	return r;
}

// GB2312 => GBK
// 中华人民共和国 --> 中華人民共和國
void GB2GBK(char *szBuf)
{
	if(!strcmp(szBuf, ""))return;
	int nStrLen = strlen(szBuf);
	DWORD wLCID = MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED), SORT_CHINESE_PRC);
	int nReturn = LCMapString(wLCID, LCMAP_TRADITIONAL_CHINESE, szBuf, nStrLen, NULL, 0);
	if(!nReturn)return;
	char *pcBuf = new char[nReturn + 1];
	__try{
		wLCID = MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED), SORT_CHINESE_PRC);
		LCMapString(wLCID, LCMAP_TRADITIONAL_CHINESE, szBuf, nReturn, pcBuf, nReturn + 1);
		strncpy(szBuf, pcBuf, nReturn);
	}
	__finally{
		delete[] pcBuf;
	}
}



void MouseScroll(){
	//如果alt键按下,则进行平移
	if(tMouseScrollMapToggle.isOn && nMouseScrollMap ==1){
		HWND hwnd = D2GetHwnd();
		POINT p;
		//先计算出鼠标相对位置
		GetCursorPos(&p);
		ScreenToClient(hwnd, &p); 
		//计算鼠标和人物的相对位置
		long x = p.x  - 400 ;
		long y =   p.y -300 ;
		MAPSHAKEX = x*3;
		MAPSHAKEY = y *3;
	}
}

void DrawCross(long newx , long newy , DWORD color ,int len)
{

	D2DrawLine(newx, newy-len,newx, newy+len, color, 100);
	D2DrawLine(newx-len, newy,newx+len, newy, color, 100);
}

void DrawMousePointer(){
	//if(tMousePosition.isOn){
		POINT ptTopLeft,ptBottomRight;
		ScreenToAutomapRelative(&ptTopLeft, 0, 0);
		ScreenToAutomapRelative(&ptBottomRight, 800, 600-48);
		// 鼠标所在位置画十字
		POINT p;

		HWND hwnd = D2GetHwnd();
		//先计算出鼠标相对位置
		GetCursorPos(&p);
		ScreenToClient(hwnd, &p);
		//ClientToScreen(hwnd,&p);
		//计算鼠标和人物的相对位置
		long addx = (long)( (ptBottomRight.x - ptTopLeft.x) * p.x/800  );
		long addy =  (long)( (ptBottomRight.y - ptTopLeft.y) * p.y/600 ) ;
		long newx = (long)( ptTopLeft.x + addx);
		long newy = (long)(ptTopLeft.y + addy);
		//小地图鼠标位置画十字
		DrawCross((long)newx,(long)newy,(DWORD)0x84 ,6);
	//}
}

