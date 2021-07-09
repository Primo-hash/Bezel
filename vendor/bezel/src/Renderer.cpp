#include "bezel/Precompiled.h"
#include "bezel/include/renderer/Renderer.h"

namespace Bezel {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::beginScene(OrthographicCamera& camera) {
		s_SceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();
	}

	void Renderer::endScene() {
	}

	void Renderer::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform) {
		// How to render
		shader->bind();
		shader->addUniformMat4("u_ViewProjection", s_SceneData->viewProjectionMatrix);
		shader->addUniformMat4("u_Transform", transform);
		// What to render
		vertexArray->bind();
		RenderCommand::drawIndexed(vertexArray);
	}
}
