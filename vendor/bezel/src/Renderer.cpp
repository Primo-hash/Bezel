#include "bezel/Precompiled.h"
#include "bezel/include/renderer/Renderer.h"

namespace Bezel {

	void Renderer::beginScene() {
	}

	void Renderer::endScene() {
	}

	void Renderer::submit(const std::shared_ptr<VertexArray>& vertexArray) {
		vertexArray->bind();
		RenderCommand::drawIndexed(vertexArray);
	}
}
