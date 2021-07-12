#include "bezel/Precompiled.h"
#include "bezel/include/App.h"
#include "bezel/include/renderer/Renderer.h"
#include "bezel/include/Input.h"

//#include "bezel/include/renderer/Renderer.h"
#include <GLFW/glfw3.h>

namespace Bezel {

	App* App::s_Instance = nullptr;

	Bezel::App::App() {
		BZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// Simple test window to check the Window class and children's functionality
		m_Window = std::unique_ptr<Window>(Window::create());

		// Default set of keyboard, mouse and application events running by default
		m_Window->setEventCallback(BZ_BIND_EVENT_FN(App::onEvent));

		// Call init of abstracted renderer
		Renderer::init();

		// Native GUI instance overlay for the application
		m_ImGuiLayer = new ImGuiLayer();
		pushOverlay(m_ImGuiLayer);
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
			
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			// Event handling by layer priority
			for (Layer* layer : m_LayerStack) {
				layer->onUpdate(timestep);
			}

			// Render GUI
			m_ImGuiLayer->begin();
			for (Layer* layer : m_LayerStack) {
				layer->onImGuiRender();
			}
			m_ImGuiLayer->end();
			m_Window->onUpdate();
		}
	}

	/*
		Uses event dispatcher to handle execution and logging of any event type.
		Checks every frame if the WindowCloseEvent has been requested, and keeps open/closes window.
	*/
	void App::onEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BZ_BIND_EVENT_FN(App::onWindowClose));

		// Handle events in reverse, where overlays have priority
		// Stops iteration if event has been handled
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
		    auto layer = (*--it);
			layer->onEvent(e);
			if (e.handled) { break; }
		}
	}
	
	void App::pushLayer(Layer* layer) {
		m_LayerStack.pushLayer(layer);
	}

	void App::popLayer(Layer* layer) {
		m_LayerStack.popLayer(layer);
	}

	void App::pushOverlay(Layer* overlay) {
		m_LayerStack.pushOverlay(overlay);
	}

	void App::popOverlay(Layer* overlay) {
		m_LayerStack.popOverlay(overlay);
	}

}