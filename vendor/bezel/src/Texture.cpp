#include "bezel/Precompiled.h"
#include "bezel/include/renderer/Texture.h"

#include "bezel/include/renderer/Renderer.h"
#include "bezel/platform/renderAPI/OpenGL/OpenGLTexture.h"

namespace Bezel {

	Ref<Texture2D> Texture2D::create(uint32_t width, uint32_t height) {
		switch (Renderer::getAPI())
		{
		case RenderAPI::API::None:    BZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::OpenGL:  return createRef<OpenGLTexture2D>(width, height);
		default: BZ_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}

	Ref<Texture2D> Texture2D::create(const std::string& path)
	{
		switch (Renderer::getAPI())
		{
		case RenderAPI::API::None:    BZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::OpenGL:  return createRef<OpenGLTexture2D>(path);
		default: BZ_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}

}