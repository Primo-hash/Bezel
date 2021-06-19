/*
*	Eksporterer bibliotek basert på platform for klasser som bruker BEZEL_API,
*   DLL blir importert hvis ikke allerede importert.

#ifdef BZ_PLATFORM_WINDOWS
	#ifdef BZ_BUILD_DLL
		#define BEZEL_API __declspec(dllexport)
	#else
		#define BEZEL_API __declspec(dllexport)
	#endif
#else
	#error "Bezel only supports Windows for now."
#endif
*/

#pragma once

// Define EXPORTED for any platform
#if defined _WIN32 || defined __CYGWIN__
#ifdef WIN_EXPORT
	// Exporting...
	#ifdef __GNUC__
		#define BEZEL_API __attribute__ ((dllexport))
	#else
		#define BEZEL_API __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
	#endif
#else

	#ifdef __GNUC__
		#define BEZEL_API __attribute__ ((dllimport))
	#else
		#define BEZEL_API __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
	#endif
#endif
	#define NOT_EXPORTED
#else
	#if __GNUC__ >= 4
		#define BEZEL_API __attribute__ ((visibility ("default")))
		#define NOT_EXPORTED  __attribute__ ((visibility ("hidden")))
	#else
		#define BEZEL_API
		#define NOT_EXPORTED
	#endif
#endif