#pragma once
/*
*	Eksporterer bibliotek basert på platform for klasser som bruker BEZEL_API,
*   DLL blir importert hvis ikke allerede importert.
*/

// Define EXPORTED for any platform
#if defined _WIN32
	# ifdef Engine_EXPORTS
		#define EXPORTED  __declspec( dllexport )
	#else
		#define EXPORTED  __declspec( dllimport )
	#endif
#else
	#if __GNUC__ >= 4
		#define EXPORTED __attribute__ ((visibility ("default")))
		#define NOT_EXPORTED  __attribute__ ((visibility ("hidden")))
	#else
		#error Unsupported platform!
	#endif
#endif

/*
	For filtrering av events i spesifikke app scenarie.
	Dette gjør at f.eks i meny så kan vi ignorere alle tastetrykk og bare ha museklikk.
*/
#define BIT(x) (1 << x)


/*
	Logging assertions based on condition parameter x.
*/
#ifdef BZ_ENABLE_ASSERTS
	#define BZ_CLIENT_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define BZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define BZ_CLIENT_ASSERT(x, ...)
	#define BZ_CORE_ASSERT(x, ...)
#endif