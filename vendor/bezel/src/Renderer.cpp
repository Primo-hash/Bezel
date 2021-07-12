#include "bezel/Precompiled.h"
#include "bezel/include/renderer/Renderer.h"

#include "bezel/platform/renderAPI/OpenGL/OpenGLShader.h"

namespace Bezel {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

 	void Renderer::init() {
		RenderCommand::init();
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
