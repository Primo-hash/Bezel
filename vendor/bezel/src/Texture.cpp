#include "bezel/Precompiled.h"
#include "bezel/include/renderer/Texture.h"

#include "bezel/include/renderer/Renderer.h"
#include "bezel/platform/renderAPI/OpenGL/OpenGLTexture.h"

namespace Bezel {

	Ref<Texture2D> Texture2D::create(const std::string& path)
	{
		switch (Renderer::getAPI())
		{
		case RenderAPI::API::None:    BZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(path);
		default: BZ_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}

}