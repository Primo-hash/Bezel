#include "bezel/Precompiled.h"
#include "bezel/include/renderer/Shader.h"

#include "bezel/include/renderer/Renderer.h"
#include "bezel/platform/renderAPI/OpenGL/OpenGLShader.h"

namespace Bezel {

	Shader* Shader::create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::getAPI()) {
		case RenderAPI::API::None:    BZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::OpenGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
		default: BZ_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}
}
