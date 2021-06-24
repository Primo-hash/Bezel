#pragma once
#include "bezel/include/Layer.h"

#include "bezel/include/events/AppEvent.h"
#include "bezel/include/events/KeyEvent.h"
#include "bezel/include/events/MouseEvent.h"

namespace Bezel {

	class EXPORTED ImGuiLayer : public Layer {
	private:
		float m_Time = 0.0f;

		bool onMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool onMouseMovedEvent(MouseMovedEvent& e);
		bool onMouseScrolledEvent(MouseScrolledEvent& e);
		bool onKeyPressedEvent(KeyPressedEvent& e);
		bool onKeyReleasedEvent(KeyReleasedEvent& e);
		bool onKeyTypedEvent(KeyTypedEvent& e);
		bool onWindowResizeEvent(WindowResizeEvent& e);
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void onAttach();
		void onDetach();
		void onUpdate();
		void onEvent(Event& event);
	};

}