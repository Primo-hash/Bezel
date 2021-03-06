#pragma once
#include "Core.h"

namespace Bezel {

	class EXPORTED Input {
	private:
		static Scope<Input> s_Instance;
	protected:
		Input() = default;
		virtual bool isKeyPressedImpl(int keycode) = 0;
		virtual bool isMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> getMousePositionImpl() = 0;
		virtual float getMouseXImpl() = 0;
		virtual float getMouseYImpl() = 0;
	public:
		Input(const Input&) = delete;
		Input& operator = (const Input&) = delete;
		inline static bool isKeyPressed(int keycode) { return s_Instance->isKeyPressedImpl(keycode); }
		inline static bool isMouseButtonPressed(int button) { return s_Instance->isMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> ietMousePosition() { return s_Instance->getMousePositionImpl(); }
		inline static float ietMouseX() { return s_Instance->getMouseXImpl(); }
		inline static float ietMouseY() { return s_Instance->getMouseYImpl(); }
	};

}
