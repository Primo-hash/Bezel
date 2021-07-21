#pragma once

#include "bezel/include/renderer/GraphicsLibraryContext.h"

struct GLFWwindow;

namespace Bezel {

	/*
		OpenGL specific implementation class for context rendering
	*/
	class OpenGLContext : public GraphicsLibraryContext {
	private:
		GLFWwindow* m_WindowHandle;
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void init() override;
		virtual void swapBuffers() override;
	};

}