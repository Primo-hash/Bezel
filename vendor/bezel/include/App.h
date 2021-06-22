#pragma once
#include "Core.h"
#include "events/Event.h"
#include "events/AppEvent.h"

#include "Window.h"

namespace Bezel {

	class EXPORTED App {
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		bool onWindowClose(WindowCloseEvent& e);
	public:
		App();
		virtual ~App();			// Arvet av applikasjoner som bruker Bezel library

		void run();				// Runs application loop
		void onEvent(Event& e);	// Handles events with dispatcher
	};

	App* createApp();		// Initiert her, og definert eksternt av klient applikasjon

}

