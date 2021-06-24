#include "bezel/Precompiled.h"
#include "bezel/include/LayerStack.h"

namespace Bezel {

	LayerStack::LayerStack() {
		m_LayerInsert = m_Layers.begin();	// Only for use by class members
	}

	LayerStack::~LayerStack() {
		// Removes all layers on destruction
		for (Layer* layer : m_Layers) {
			delete layer;
		}
	}

	/*
		Pushes layer object to the specified beginning of the stack
	*/
	void LayerStack::pushLayer(Layer* layer) {
		// Insert Layer at the beginning of the vector
		// Allocate more space if needed
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
	}

	/*
		Pushes overlay layer object to the specified beginning of the stack
	*/
	void LayerStack::pushOverlay(Layer* overlay) {
		// Insert Layer at the beginning of the vector
		// Allocate more space if needed
		m_Layers.emplace_back(overlay);
	}

	/*
		Pops layer from the end of the stack.
	*/
	void LayerStack::popLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			m_LayerInsert--;		// Moves starting pointer one element backward
		}
	}

	/*
		Pops overlay layer from the end of the stack.
	*/
	void LayerStack::popOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
		}
	}
}
