#include "bezel/Precompiled.h"
#include "bezel/include/renderer/Buffer.h"

#include "bezel/platform/renderAPI/OpenGL/OpenGLBuffer.h"
#include "bezel/include/renderer/Renderer.h"

#include <glad/glad.h>

namespace Bezel {

	VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size) {
		switch (Renderer::getAPI()) {
		case RenderAPI::API::None:
			BZ_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		default:
			BZ_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}

	unsigned int VertexBuffer::getOpenGLVersion() {
		int major = GLVersion.major;
		int minor = GLVersion.minor;
		return major * 100 + minor * 10;
	}

	IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t size) {
		switch (Renderer::getAPI()) {
		case RenderAPI::API::None:
			BZ_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			return nullptr;
		case RenderAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
		default:
			BZ_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
}
