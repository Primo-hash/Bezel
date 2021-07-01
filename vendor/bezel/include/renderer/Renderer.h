#pragma once

/*
	Rendering is built around the concept that the developer can switch between
	Graphics libraries (OpenGL, Vulkan, DirectX, etc.) after compilation instead of
	having to compile all over again if the developer needs to switch the library needed.
	However incompatible libraries won't compile on runtime like DirectX in an Apple machine.
*/

namespace Bezel {

	enum class RenderAPI {
		None = 0, OpenGL = 1, DirectX12 = 2, Vulkan = 3, Metal = 4
	};

	class Renderer {
	private:
		static RenderAPI s_RenderAPI;
	public:
		inline static RenderAPI getAPI() { return s_RenderAPI; }
	};

}
