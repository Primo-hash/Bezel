#include "bezel/Precompiled.h"
#include "bezel/include/renderer/GraphicsLibraryContext.h"

#include "bezel/include/renderer/Renderer.h"
#include "bezel/platform/renderAPI/OpenGL/OpenGLContext.h"

namespace Bezel {

	Scope<GraphicsLibraryContext> GraphicsLibraryContext::create(void* window) {
		switch (Renderer::getAPI()) {
		case RenderAPI::API::None:    BZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::OpenGL:  return createScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		default: BZ_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}

	}

}