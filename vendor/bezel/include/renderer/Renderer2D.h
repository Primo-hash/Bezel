#pragma once

#include "OrthographicCamera.h"
#include "Texture.h"

namespace Bezel {

	class Renderer2D {
	public:
		static void init();
		static void shutdown();

		static void beginScene(const OrthographicCamera& camera);
		static void endScene();

		// Primitives
		static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		// w/Texture
		static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tileCount = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tileCount = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		
		// Primitives w/Rotation
		static void drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		// w/Texture
		static void drawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tileCount = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void drawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tileCount = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	};

}