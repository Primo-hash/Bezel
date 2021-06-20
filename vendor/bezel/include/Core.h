/*
*	Eksporterer bibliotek basert på platform for klasser som bruker BEZEL_API,
*   DLL blir importert hvis ikke allerede importert.
*/


#pragma once

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
		#define EXPORTED
		#define NOT_EXPORTED
	#endif
#endif


/*
	For filtering events in certain application scenarios.
	This allows for ignoring or focusing on certain events based on category.
	For filtrering av events i spesifikke app scenarie.
	Dette gjør at f.eks i meny så kan vi ignorere alle tastetrykk og bare ha museklikk.
*/
#define BIT(x) (1 << x)