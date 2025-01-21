#include "dkpch.h"
#include "LayerManager.h"
#include "Dark/Core.h"

namespace Dark {

	void LayerManager::pushLayer(s_Layer& layer)
	{
		m_layers.insert(m_layers.begin(), layer);
	}

	void LayerManager::pushLayerEnd(s_Layer& layer)
	{
		m_layers.push_back(layer);
	}

	void LayerManager::popLayer(s_Layer& layer)
	{
		layer->OnDetach();
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end())
		{
			m_layers.erase(it);
		}
	}

}