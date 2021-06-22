#include "bezel/Precompiled.h"
#include "bezel/include/App.h"
#include "bezel/include/Log.h"

#include <GLFW/glfw3.h>

namespace Bezel {

	// Usage of bind here a bit complicated, but I understand that this macro
	// needs to fulfill a certain condition to run the event appended as a parameter.
	#define BIND_EVENT_FN(x) std::bind(&App::x, this, std::placeholders::_1)

	Bezel::App::App() {
		// Simple test window to check the Window class and children's functionality
		m_Window = std::unique_ptr<Window>(Window::create());
		// Default set of keyboard, mouse and application events running by default
		m_Window->setEventCallback(BIND_EVENT_FN(onEvent));
	}

	Bezel::App::~App() {

	}

	/*
		Returns signal to close the referenced application window
		and sets values to represent shutdown.
	*/
	bool App::onWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	void Bezel::App::run() {
		// Simple window test
		while (m_Running) {
			float i = 0.01;
			glClearColor(1 - i, 0.3, 0.5, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->onUpdate();
		}
	}

	/*
		Uses event dispatcher to handle execution and logging of any event type.
		Checks every frame if the WindowCloseEvent has been requested, and keeps open/closes window.
	*/
	void App::onEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

		BZ_CORE_TRACE("{0}", e);	// Any event type is logged 
	}
	

}