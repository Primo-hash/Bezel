#pragma once

namespace Bezel {

	/*
		Used for setting up a rendering context for a window based on
		which graphics library.
		Pure virtual class to be implemented by children.
	*/
	class RenderContext {
	public:
		virtual void init() = 0;
		virtual void swapBuffers() = 0;
	};

}