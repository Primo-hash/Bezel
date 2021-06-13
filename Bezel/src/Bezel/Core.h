#pragma once

/*
*	Eksporterer bibliotek basert på platform for klasser som bruker BEZEL_API,
*   DLL blir importer hvis ikke allerede importert.
*/
#ifdef BZ_PLATFORM_WINDOWS
	#ifdef BZ_BUILD_DLL
		#define BEZEL_API __declspec(dllexport)
	#else
		#define BEZEL_API __declspec(dllexport)
	#endif
#else
	#error "Bezel only supports Windows for now."
#endif