#include "bezel/Precompiled.h"
#include "OpenGLFuncVersion.h"

#include <glad/glad.h>

namespace Bezel {
	/*
		Returns current OpenGL version as an int i.e v4.5 = 450
	*/
	unsigned int OpenGLFuncVersion::getOpenGLVersion() {
		int major = GLVersion.major;
		int minor = GLVersion.minor;
		return major * 100 + minor * 10;
	}
}
