#pragma once
#include "bezel/include/renderer/RenderAPI.h"

namespace Bezel {

	class OpenGLRenderAPI : public RenderAPI {
	public:
		virtual void setClearColor(const glm::vec4& color) override;
		virtual void clear() override;

		virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};

}