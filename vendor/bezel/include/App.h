#pragma once
#include "Core.h"

#include "Window.h"
#include "bezel/include/LayerStack.h"

#include "events/Event.h"
#include "events/AppEvent.h"

#include "bezel/core/Timestep.h"

#include "bezel/GUI/ImGui/ImGuiLayer.h"

namespace Bezel {

	class EXPORTED App {
	private:
		static App* s_Instance;			// Application instance called by client
		bool m_Running = true;			// Current application instance status
		float m_LastFrameTime = 0.0f;	// Time of last frame for this app

		std::unique_ptr<Window> m_Window;
		
		// General layer/overlay stack
		LayerStack m_LayerStack;
		
		// GUI
		ImGuiLayer* m_ImGuiLayer;

		bool onWindowClose(WindowCloseEvent& e);
	public:
		App();
		virtual ~App();			// Arvet av applikasjoner som bruker Bezel library

		void run();				// Runs application loop
		void onEvent(Event& e);	// Handles events with dispatcher

		// Returns pointer to application window
		inline Window& getWindow() { return *m_Window; }

		// returns pointer to application instance
		inline static App& get() { return *s_Instance; }

		void pushLayer(Layer* layer);		// Inserts layer to LayerStack
		void popLayer(Layer* layer);		// Pops a layer from the LayerStack
		void pushOverlay(Layer* overlay);	// Integrated functions for overlay layers to better identify overlays
		void popOverlay(Layer* overlay);
	};

	App* createApp();		// Initiert her, og definert eksternt av klient applikasjon

}

