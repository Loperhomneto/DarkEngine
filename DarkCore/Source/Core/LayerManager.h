#pragma once
#include "Layer.h"
#include <vector>
#include <memory>

namespace Dark {

	using s_Layer = std::shared_ptr<Layer>;
	using iterator = std::vector<s_Layer>::iterator;
	using const_iterator = std::vector<s_Layer>::const_iterator;

	class LayerManager
	{
	private:
		std::vector<s_Layer> m_layers;
	public:
		LayerManager() {};
		~LayerManager() {};
		void pushLayer(s_Layer& layer);
		void pushLayerEnd(s_Layer& layer);
		void popLayer(s_Layer& layer);

		iterator begin() { return m_layers.begin(); };
		iterator end() { return m_layers.end(); };
		const_iterator begin() const { return m_layers.end(); };
		const_iterator end() const { return m_layers.end(); };

		s_Layer operator()(iterator it) { return m_layers[std::distance(m_layers.begin(), it)]; }
	};

}