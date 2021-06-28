#include "bezel/Precompiled.h"
#include "DesktopWindow.h"

#include "bezel/include/events/AppEvent.h"
#include "bezel/include/events/MouseEvent.h"
#include "bezel/include/events/KeyEvent.h"

// Rendering context
#include "renderAPI/OpenGL/OpenGLContext.h"

namespace Bezel {

	static bool s_GLFWInitialized = false;

	// FUNCTIONS

	/*
		Error handler for GLFW function callbacks, prints error and description.
	*/
	static void GLFWErrorCallback(int error, const char* desc) {
		BZ_CORE_ERROR("GLFW Error ({0}): {1}", error, desc); 
	}



	// CLASS FUNCTIONS

	/*
		Returns pointer to new Window object initialized with WindowSpecs object parameter
	*/
	Window* Window::create(const WindowSpecs& specs)
	{
		return new DesktopWindow(specs);
	}

	/*
		Sets up window data on window object creation
	*/
	DesktopWindow::DesktopWindow(const WindowSpecs& specs)
	{
		init(specs);
	}

	DesktopWindow::~DesktopWindow()
	{
		shutdown();
	}

	/*
		Initializes desktop window with specified data by user.
		Logs window specs while creating.
	*/
	void DesktopWindow::init(const WindowSpecs& specs)
	{
		m_Data.title = specs.title;
		m_Data.width = specs.width;
		m_Data.height = specs.height;

		BZ_CORE_INFO("Creating window {0} ({1}, {2})", specs.title, specs.width, specs.height);

		if (!s_GLFWInitialized)	// GLFW initialization with error logging
		{
			int success = glfwInit();
			BZ_CORE_ASSERT(success, "Could not intialize GLFW!");

			// Ensures GLFW Errors are printed with the Bezel logging system
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)specs.width, (int)specs.height, m_Data.title.c_str(), nullptr, nullptr);
		// Set OpenGL to render the context
		m_Context = new OpenGLContext(m_Window);
		m_Context->init();

		glfwSetWindowUserPointer(m_Window, &m_Data);	
		setVSync(true);								// Vsync on by default
	
		/*
		The following callback functions utilize the GLFW library to abstract window events
		while tying them to a certain application's window object (possibly multiple).
		This allows us to customize certain events for the window like logging events while executing them
		since the GLFW functions allow the passing of certain functions to be executed after the desired event.

		These functions are made using lambdas and are tied to each Window object on construction respectively
		This allows us to create Windows with different Events implemented based on different init functions they were initialized with.
		*/
		
		/*
			Callback function glfwSetWindowSizeCallback for logging the resizing of the window.
		*/
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);	// Shorten GLFW window name pointer to data.
			data.width = width;
			data.height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});
	
		/*
			Callback function glfwSetWindowCloseCallback for logging the termination of the window.
		*/
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		/*
			Callback function glfwSetKeyCallback for the use of keys within the window.
		*/
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			// We have made events for each of these key actions allowing better control of them.
			// An example would be the repeat event being executed a limited number of times instead of continuing.
			// This allows for better limiting or increasing player controls.
			switch (action) {
			case GLFW_PRESS:	
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		/*
			Callback function glfwSetCharCallback for registering key typing (ex. in a textbox) and logging the event.
		*/
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

		/*
			For handling and logging mouse click events
		*/
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		/*
			For handling and logging mouse scroll events
		*/
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		/*
			For handling and logging mouse movement events
		*/
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}


	// The following functions are basic window actions to be utilized 
	// by callback functions or the like.

	void DesktopWindow::shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void DesktopWindow::onUpdate()
	{
		glfwPollEvents();
		m_Context->swapBuffers();
	}

	void DesktopWindow::setVSync(bool enabled)
	{
		if (enabled)	// Set vsync based on GLFW lib functions
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool DesktopWindow::isVSync() const
	{
		return m_Data.VSync;
	}

}