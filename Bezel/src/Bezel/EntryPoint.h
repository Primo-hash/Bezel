#pragma once
#include "App.h"

/*
*	EntryPoint.h setter opp engine applikasjonen til å kjøre når en
*	ekstern applikasjon lenker til Bezel
*/

#ifdef BZ_PLATFORM_WINDOWS

extern Bezel::App* Bezel::createApp();

int main(int argc, char** argv) {
	// Intro
	std::cout << "Running with Bezel engine\n";

	// Definer base applikasjon
	auto app = Bezel::createApp();
	app->run();
	delete app;
}

#endif