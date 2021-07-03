#pragma once
#include "RenderCommand.h"

/*
	Rendering is built around the concept that the developer can switch between
	Graphics libraries (OpenGL, Vulkan, DirectX, etc.) after compilation instead of
	having to compile all over again if the developer needs to switch the library needed.
	However incompatible libraries won't compile on runtime like DirectX in an Apple machine.
*/

namespace Bezel {

	class Renderer {
	public:
		static void beginScene();
		static void endScene();

		static void submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RenderAPI::API getAPI() { return RenderAPI::getAPI(); }

	};

}
