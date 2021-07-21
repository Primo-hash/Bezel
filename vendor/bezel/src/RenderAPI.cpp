#include "bezel/Precompiled.h"
#include "bezel/include/renderer/RenderAPI.h"

// Currently supported library APIs
#include "bezel/platform/renderAPI/OpenGL/OpenGLRenderAPI.h"	// OpenGL

namespace Bezel {

	RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL;

	Scope<RenderAPI> RenderAPI::create() {
		switch (s_API) {
		case RenderAPI::API::None:    BZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::OpenGL:  return createScope<OpenGLRenderAPI>();
		default: BZ_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}
}
