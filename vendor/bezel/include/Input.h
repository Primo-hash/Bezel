#pragma once
#include "Core.h"

namespace Bezel {

	class EXPORTED Input {
	private:
		static Input* s_Instance;
	protected:
		virtual bool isKeyPressedImpl(int keycode) = 0;
		virtual bool isMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> getMousePositionImpl() = 0;
		virtual float getMouseXImpl() = 0;
		virtual float getMouseYImpl() = 0;
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->isKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->isMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->getMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->getMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->getMouseYImpl(); }
	};

}
