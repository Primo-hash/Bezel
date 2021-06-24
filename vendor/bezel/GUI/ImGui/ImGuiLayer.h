#pragma once

#include "bezel/include/Layer.h"

namespace Bezel {

	class EXPORTED ImGuiLayer : public Layer {
	private:
		float m_Time = 0.0f;
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void onAttach();
		void onDetach();
		void onUpdate();
		void onEvent(Event& event);
	};

}