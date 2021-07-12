#pragma once

namespace Bezel {

	/*
		This class can be used to define OpenGL functions based on current running
		version of OpenGL, versions below 4.5 will use glGen, while above will use glCreate.
		*/
	class OpenGLFuncVersion {
	public:
		OpenGLFuncVersion();
		virtual ~OpenGLFuncVersion();

		static unsigned int getOpenGLVersion();
	};

}
