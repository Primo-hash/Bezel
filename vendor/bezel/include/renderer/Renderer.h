#pragma once
#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Shader.h"

/*
	This renderer is built around the concept that the developer can switch between
	Graphics libraries (OpenGL, Vulkan, DirectX, etc.) after compilation instead of
	having to compile all over again if the developer needs to switch the library needed.
	However incompatible libraries won't compile on runtime like DirectX in an Apple product.
*/

namespace Bezel {

	class Renderer {
	private:
		struct SceneData {
			glm::mat4 viewProjectionMatrix;
		};
		
		static SceneData* s_SceneData;
	public:
		static void init();

		static void beginScene(OrthographicCamera &camera);
		static void endScene();

		static void submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RenderAPI::API getAPI() { return RenderAPI::getAPI(); }

	};

}
