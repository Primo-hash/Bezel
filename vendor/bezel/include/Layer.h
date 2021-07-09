#pragma once

/*
	The Layer.h header is used along with the LayerStack.h header to create a
	layer stack system.
*/

#include "Core.h"
#include "bezel/core/Timestep.h"
#include "events/Event.h"

namespace Bezel {

	/*
		The Layer class is part of the layer stack system implemented for the Bezel engine.
		By layering the draw execution on the application window the developer has better controll
		over drawing resources. See LayerStack Class for more information.
	*/
	class EXPORTED Layer {
	protected:
		std::string m_DebugName;	// For identifying layers in debug mode
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate(Timestep ts) {}
		virtual void onImGuiRender() {}
		virtual void onEvent(Event& event) {}

		inline const std::string& getName() const { return m_DebugName; }
	};

}
