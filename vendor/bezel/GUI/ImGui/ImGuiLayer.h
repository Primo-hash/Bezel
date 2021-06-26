#pragma once
#include "bezel/include/Layer.h"

#include "bezel/include/events/AppEvent.h"
#include "bezel/include/events/KeyEvent.h"
#include "bezel/include/events/MouseEvent.h"

namespace Bezel {

	class EXPORTED ImGuiLayer : public Layer {
	private:
		float m_Time = 0.0f;

	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onImGuiRender() override;

		void begin();	// ImGui frame definition start
		void end();		// ImGui frame definition stop
	};

}