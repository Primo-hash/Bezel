/*
	Implementation of input polling for desktop platforms.
	Allows uses like asking if certain keys er being pressed
	to base functions off of.

	Currently using GLFW so both UNIX and WINDOWS use the same functions
*/

#include "bezel/Precompiled.h"
#include "DesktopInput.h"

#include "bezel/include/App.h"
#include <GLFW/glfw3.h>

namespace Bezel {

	Input* Input::s_Instance = new DesktopInput();

	bool DesktopInput::isKeyPressedImpl(int keycode) {
		#if defined BZ_PLATFORM_WINDOWS
			auto window = static_cast<GLFWwindow*>(App::get().getWindow().getNativeWindow());
			auto state = glfwGetKey(window, keycode);
			return state == GLFW_PRESS || state == GLFW_REPEAT;
		#elif defined BZ_PLATFORM_UNIX
			auto window = static_cast<GLFWwindow*>(App::get().getWindow().getNativeWindow());
			auto state = glfwGetKey(window, keycode);
			return state == GLFW_PRESS || state == GLFW_REPEAT;
		#endif
	}

	bool DesktopInput::isMouseButtonPressedImpl(int button) {
		#if defined BZ_PLATFORM_WINDOWS
			auto window = static_cast<GLFWwindow*>(App::get().getWindow().getNativeWindow());
			auto state = glfwGetMouseButton(window, button);
			return state == GLFW_PRESS;
		#elif defined BZ_PLATFORM_UNIX
			auto window = static_cast<GLFWwindow*>(App::get().getWindow().getNativeWindow());
			auto state = glfwGetMouseButton(window, button);
			return state == GLFW_PRESS;
		#endif
	}

	std::pair<float, float> DesktopInput::getMousePositionImpl() {
		#if defined BZ_PLATFORM_WINDOWS
			auto window = static_cast<GLFWwindow*>(App::get().getWindow().getNativeWindow());
			double xPos, yPos;
			glfwGetCursorPos(window, &xPos, &yPos);
			return { (float)xPos, (float)yPos };
		#elif defined BZ_PLATFORM_UNIX
			auto window = static_cast<GLFWwindow*>(App::get().getWindow().getNativeWindow());
			double xPos, yPos;
			glfwGetCursorPos(window, &xPos, &yPos);
			return { (float)xPos, (float)yPos };
		#endif
	}

	float DesktopInput::getMouseXImpl() {
		#if defined BZ_PLATFORM_WINDOWS
			auto [x, y] = getMousePositionImpl();
			return x;
		#elif defined BZ_PLATFORM_LINUX
			auto [x, y] = getMousePositionImpl();
			return x;
		#endif
	}

	float DesktopInput::getMouseYImpl() {
		#if defined BZ_PLATFORM_WINDOWS
			auto [x, y] = getMousePositionImpl();
			return y;
		#elif defined BZ_PLATFORM_LINUX
			auto [x, y] = getMousePositionImpl();
			return y;
		#endif
	}
}
