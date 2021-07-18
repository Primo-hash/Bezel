#pragma once
#include "RenderAPI.h"

namespace Bezel {

	class RenderCommand {
	private:
		static Scope<RenderAPI> s_RenderAPI;
	public:
		inline static void init() { s_RenderAPI->init(); }
		inline static void setClearColor(const glm::vec4& color) { s_RenderAPI->setClearColor(color); }
		inline static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { s_RenderAPI->setViewport(x, y, width, height); }
		inline static void clear() { s_RenderAPI->clear(); }
		inline static void drawIndexed(const Ref<VertexArray>& vertexArray) { s_RenderAPI->drawIndexed(vertexArray); }
	};

}
