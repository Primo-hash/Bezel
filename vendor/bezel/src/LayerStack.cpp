#include "bezel/Precompiled.h"
#include "bezel/include/LayerStack.h"
namespace Bezel {

	LayerStack::LayerStack() {
		
	}

	LayerStack::~LayerStack() {
		// Removes all layers on destruction
		for (Layer* layer : m_Layers) {
			layer->onDetach();	// protocol before deletion
			delete layer;
		}
	}

	/*
		Pushes layer object to the specified beginning of the stack
	*/
	void LayerStack::pushLayer(Layer* layer) {
		// Insert Layer at the beginning of the vector
		// Allocate more space if needed
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
		layer->onAttach();
	}

	/*
		Pushes overlay layer object to the specified beginning of the stack
	*/
	void LayerStack::pushOverlay(Layer* overlay) {
		// Insert Layer at the beginning of the vector
		// Allocate more space if needed
		m_Layers.emplace_back(overlay);
		overlay->onAttach();
	}

	/*
		Pops layer from the end of the stack.
	*/
	void LayerStack::popLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
		if (it != m_Layers.begin() + m_LayerInsertIndex) {
			layer->onDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;		// Moves starting pointer one element backward
		}
	}

	/*
		Pops overlay layer from the end of the stack.
	*/
	void LayerStack::popOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
		if (it != m_Layers.end()) {
			overlay->onDetach();
			m_Layers.erase(it);
		}
	}
}
