#pragma once
/*
	A desktop implementation of the 'Input' class in Input.h.
	This class is meant to be implemented for the Engine windows as a single instance.
	Instead of creating a separate input polling instance for each window.
*/

#include "bezel/include/Input.h"

namespace Bezel {

	class DesktopInput : public Input {
	protected:
		// Keyboard
		virtual bool isKeyPressedImpl(int keycode) override;

		// Mouse
		virtual bool isMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> getMousePositionImpl() override;
		virtual float getMouseXImpl() override;
		virtual float getMouseYImpl() override;
	};

}
