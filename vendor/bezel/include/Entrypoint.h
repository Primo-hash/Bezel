#pragma once
#include <iostream>
#include "Log.h"
#include "App.h"

/*
*	EntryPoint.h setter opp engine applikasjonen til å kjøre når en
*	ekstern applikasjon lenker til Bezel
*/
extern Bezel::App* Bezel::createApp();

int main(int argc, char** argv) {
	// Intro
	std::cout << "Running with Bezel engine\n";

	// Logger
	Bezel::Log::init();
	BZ_CORE_WARN("Log initialized!");

	// Definer base applikasjon
	auto app = Bezel::createApp();
	app->run();
	delete app;
	return 0;
}

