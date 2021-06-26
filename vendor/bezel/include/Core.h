#pragma once
/*
*	Eksporterer bibliotek basert på platform for klasser som bruker BEZEL_API,
*   DLL blir importert hvis ikke allerede importert.
*/

// Define EXPORTED for any platform
#if defined BZ_PLATFORM_WINDOWS
	#ifdef BZ_EXPORTS
		#define EXPORTED  __declspec( dllexport )
	#else
		#define EXPORTED  __declspec( dllimport )
	#endif
#elif defined BZ_PLATFORM_UNIX
	#ifdef BZ_EXPORTS
		#define EXPORTED __attribute__ ((visibility ("default")))
		#define NOT_EXPORTED  __attribute__ ((visibility ("hidden")))
	#else
		#define EXPORTED
		#define NOT_EXPORTED
	#endif
#else
	#error The program might be running on an unsupported platform, supported platforms(WINDOWS, UNIX)
#endif

/*
	Checks if Debugging mode enabled
*/
#ifdef BZ_DEBUG
	#define BZ_ENABLE_ASSERTS
#endif

/*
	Logging assertions based on condition parameter x.
*/
#ifdef BZ_ENABLE_ASSERTS
	#define BZ_CLIENT_ASSERT(x, ...) { if(!(x)) { BZ_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define BZ_CORE_ASSERT(x, ...) { if(!(x)) { BZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define BZ_CLIENT_ASSERT(x, ...)
	#define BZ_CORE_ASSERT(x, ...)
#endif

/*
	For filtrering av events i spesifikke app scenarie.
	Dette gjør at f.eks i meny så kan vi ignorere alle tastetrykk og bare ha museklikk.
*/
#define BIT(x) (1 << x)

/*
	For binding custom Bezel events to GUI or renderer functions
*/
#define BZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)