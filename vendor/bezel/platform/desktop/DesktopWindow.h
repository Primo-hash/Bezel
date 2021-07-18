#pragma once
/*
	NOTE: This subclass of the Window class in Window.h is divided to allow
	further crossplatform development and Optimization with different OS systems.

	For example compatibility with Android which uses 'surfaces' instead of 'windows', and optimizing with platform
	specific graphics libraries like DIRECTX on windows.

	The current DesktopWindow subclass should be able to handle Windows and Linux since it purely uses OpenGL
*/

#include "bezel/include/Window.h"
#include "bezel/include/renderer/RenderContext.h"

namespace Bezel {

	class DesktopWindow : public Window {
	private:
		GLFWwindow* m_Window;
		Scope<RenderContext> m_Context;

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

		virtual void init(const WindowSpecs& specs);
		virtual void shutdown();
	public:
		DesktopWindow(const WindowSpecs& specs);
		virtual ~DesktopWindow();

		void onUpdate() override;

		inline unsigned int getWidth() const override { return m_Data.width; }
		inline unsigned int getHeight() const override { return m_Data.height; }

		// Attributes
		inline void setEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void setVSync(bool enabled) override;
		bool isVSync() const override;

		// To get native window types like GLFWwindow from GLFW for example.
		inline virtual void* getNativeWindow() const { return m_Window; }
	};
}

