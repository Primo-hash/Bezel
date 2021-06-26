#pragma once
/*
	The Window.h file handles window events and is an abstract representation of a window
*/


#include "bezel/Precompiled.h"

#include "Core.h"
#include "events/Event.h"

#include "GLFW/glfw3.h"

namespace Bezel {

	/*
		Stores specified window parameters
	*/
	struct WindowSpecs
	{
		std::string title;
		unsigned int width, height;

		WindowSpecs(const std::string& title = "Bezel Engine", unsigned int width = 1080, unsigned int height = 720) 
			: title(title), width(width), height(height) {}
	};

	/* 
		Purely an interface class representing a desktop system based Window
	*/
	class EXPORTED Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void onUpdate() = 0;	// Runs a series of functions for each frame

		// Retrieves the application window width
		virtual unsigned int getWidth() const = 0;
		// Retrieves the application window height
		virtual unsigned int getHeight() const = 0;

		// Window attributes
		virtual void setEventCallback(const EventCallbackFn& callback) = 0;	
		virtual void setVSync(bool enabled) = 0;	// Enable/disable vsync
		virtual bool isVSync() const = 0;			// Checks if vsync enabled/disabled

		// To get native window types like GLFWwindow from GLFW for example.
		virtual void* getNativeWindow() const = 0;

		// Returns pointer to a new Window object
		static Window* create(const WindowSpecs& props = WindowSpecs());
	};

}