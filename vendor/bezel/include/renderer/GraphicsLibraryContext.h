#pragma once

namespace Bezel {

	class GraphicsLibraryContext {
	public:
		virtual void init() = 0;
		virtual void swapBuffers() = 0;

		static Scope<GraphicsLibraryContext> create(void* window);
	};

}
