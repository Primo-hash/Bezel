#pragma once
#include "RenderAPI.h"

namespace Bezel {

	class RenderCommand {
	private:
		static RenderAPI* s_RenderAPI;
	public:
		inline static void init() { s_RenderAPI->init(); }
		inline static void setClearColor(const glm::vec4& color) { s_RenderAPI->setClearColor(color); }
		inline static void clear() { s_RenderAPI->clear(); }
		inline static void drawIndexed(const Ref<VertexArray>& vertexArray) { s_RenderAPI->drawIndexed(vertexArray); }
	};

}
