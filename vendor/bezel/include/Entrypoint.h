#pragma once
#include <iostream>
#include "Log.h"
#include "App.h"


/*
*	EntryPoint.h setter opp engine applikasjonen til � kj�re n�r en
*	ekstern applikasjon lenker til Bezel
*/
extern Bezel::App* Bezel::createApp();

int main(int argc, char** argv) {
	// Intro
	std::cout << "Running with Bezel engine\n";

	// Logger
	Bezel::Log::Init();
	BZ_CORE_WARN("Log initialized!");
	int a = 5000;
	BZ_CLIENT_INFO("This is information! Var={0}", a);

	// Definer base applikasjon
	auto app = Bezel::createApp();
	app->run();
	delete app;
	return 0;
}
