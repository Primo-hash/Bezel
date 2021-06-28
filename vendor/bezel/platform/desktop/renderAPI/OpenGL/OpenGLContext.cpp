#include "bezel/Precompiled.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/gl.h>	// keep gl.h lowercase for linux

namespace Bezel {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {
		BZ_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BZ_CORE_ASSERT(status, "Failed to initialize Glad!");
	}

	void OpenGLContext::swapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}

}