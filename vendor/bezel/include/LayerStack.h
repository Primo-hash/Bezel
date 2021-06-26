#pragma once
/*
	The LayerStack.h header is used along with the Layer.h header to create a
	layer stack system by acting as a container class for Layer objects.
*/
#include "Core.h"
#include "Layer.h"

#include <vector>

namespace Bezel {

	/*
		The LayerStack class is part of the layer stack system implemented for the Bezel engine.
		By layering the draw execution on the application window the application can:
			* Turn on and off draw clusters based on layer
			* Ordering based on which layer gets to draw first
			* Ordering based on which layer receives events first.
			* Integrating overlay draw priority

		NOTE: Ordering layers allows us to draw overlays last, and to give priority to
			  game/app content. Ordering which layer handles events first, gives us the
			  ability to give priority to overlays when events happen.
			  An example would be clicking on a button in the GUI of an fps shooter.
			  By giving the overlay priority the button will execute while the player doesn't
			  shoot randomly in the game because the overlay blocks it by tagging the event as handled.
	*/
	class EXPORTED LayerStack {
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	public:
		LayerStack();
		~LayerStack();

		void pushLayer(Layer* layer);		// Inserts layer to LayerStack
		void popLayer(Layer* layer);		// Pops a layer from the LayerStack
		void pushOverlay(Layer* overlay);	// Integrated functions for overlay layers to better identify overlays
		void popOverlay(Layer* overlay);

		// Predefined pointers to access contained Layer objects
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	};

}
