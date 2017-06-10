#pragma once


#define CA2_BASIS 1
#define CA2_STAGE 10




#include "product.version.config.h"





BEGIN_EXTERN_C


int _ca_is_basis();
int _ca_is_stage();



#ifndef WINDOWS





typedef struct {
	unsigned int dwOSVersionInfoSize;
	unsigned int dwMajorVersion;
	unsigned int dwMinorVersion;
	unsigned int dwBuildNumber;
	unsigned int dwPlatformId;
	char szCSDVersion[128];
} OSVERSIONINFOA, *POSVERSIONINFOA, *LPOSVERSIONINFOA;

typedef struct {
	unsigned int dwOSVersionInfoSize;
	unsigned int dwMajorVersion;
	unsigned int dwMinorVersion;
	unsigned int dwBuildNumber;
	unsigned int dwPlatformId;
	char szCSDVersion[128];
	unsigned short wServicePackMajor;
	unsigned short wServicePackMinor;
	unsigned short wSuiteMask;
	unsigned char wProductType;
	unsigned char wReserved;
} OSVERSIONINFOEXA, *POSVERSIONINFOEXA, *LPOSVERSIONINFOEXA;

#endif


WINBOOL get_version_ex_a(LPOSVERSIONINFOA lpVersionInformation);



END_EXTERN_C





