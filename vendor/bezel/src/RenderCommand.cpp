#include "bezel/Precompiled.h"
#include "bezel/include/renderer/RenderCommand.h"

#include "bezel/platform/renderAPI/OpenGL/OpenGLRenderAPI.h"

namespace Bezel {

	RenderAPI* RenderCommand::s_RenderAPI = new OpenGLRenderAPI;

}