#include "bezel/Precompiled.h"
#include "OpenGLRenderAPI.h"

#include <glad/glad.h>

namespace Bezel {

	void OpenGLRenderAPI::init() {
		// Turn on blending for OpenGL
		glEnable(GL_BLEND);
		// When blending use the inverse of src texture to determine drawing priority
		// In this case the destination texture is only drawn if RGBA values of src are 0
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRenderAPI::setClearColor(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderAPI::clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderAPI::drawIndexed(const Ref<VertexArray>& vertexArray) {
		glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}

}