#pragma once
#include <iostream>
#include "Core.h"


namespace Bezel {

	class EXPORTED App {
	private:
	public:
		App();
		virtual ~App();		// Arvet av applikasjoner som bruker Bezel library

		void run();

	};

	App* createApp();		// Initiert her, og definert eksternt av klient applikasjon

}

