// crt0tdll.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/13/06 (mv)

#include "StdAfx.h"

#ifdef WINDOWS

BOOL WINAPI DllMain(HANDLE, DWORD, LPVOID);

EXTERN_C BOOL WINAPI _DllMainCRTStartup(HANDLE hInst, DWORD reason, LPVOID imp)
{

	if (reason == DLL_PROCESS_ATTACH)
	{
      //Sleep(15 * 1000);
      //MessageBox(NULL, "iexca2.dll PROCESS ATTACH", "iexca2.dll", MB_OK);
      initialize_primitive_heap();
		_init_atexit();
		_init_file();
		_initterm(__xc_a, __xc_z);
	}

	BOOL ret = DllMain(hInst, reason, imp);

	if (reason == DLL_PROCESS_DETACH)
	{
		_doexit();
      finalize_primitive_heap();
	}

	return ret;
}

#endif
