#include "bezel/Precompiled.h"
#include "bezel/include/renderer/VertexArray.h"

#include "bezel/include/renderer/Renderer.h"
#include "bezel/platform/renderAPI/OpenGL/OpenGLVertexArray.h"

namespace Bezel {

	Ref<VertexArray> VertexArray::create() {
		switch (Renderer::getAPI()) {
		case RenderAPI::API::None:    BZ_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::OpenGL:  return createRef<OpenGLVertexArray>();
		default: BZ_CORE_ASSERT(false, "Unknown RenderAPI!"); return nullptr;
		}
	}

}
