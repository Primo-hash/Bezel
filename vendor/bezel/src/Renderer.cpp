#include "bezel/Precompiled.h"
#include "bezel/include/renderer/Renderer.h"
#include "bezel/include/renderer/Renderer2D.h"

#include "bezel/platform/renderAPI/OpenGL/OpenGLShader.h"


namespace Bezel {

	Scope<Renderer::SceneData> Renderer::s_SceneData = createScope<Renderer::SceneData>();

 	void Renderer::init() {
		RenderCommand::init();
		Renderer2D::init();
	}

	void Renderer::onWindowResize(uint32_t width, uint32_t height) {
		RenderCommand::setViewport(0, 0, width, height);
	}

	void Renderer::beginScene(OrthographicCamera& camera) {
		s_SceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();
	}

	void Renderer::endScene() {
	}

	void Renderer::submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform) {
		// How to render
		shader->bind();
		// Following dynamic ptr makes renderer dependent on OpenGL, will be fixed in the future.
		std::dynamic_pointer_cast<OpenGLShader>(shader)->addUniformMat4("u_ViewProjection", s_SceneData->viewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->addUniformMat4("u_Transform", transform);
		
		// What to render
		vertexArray->bind();
		RenderCommand::drawIndexed(vertexArray);
	}
}
