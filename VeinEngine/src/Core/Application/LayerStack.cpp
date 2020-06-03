#include "vnpch.h"
#include "Core/Application/LayerStack.h"

#include "Core/Application/Layer.h"

namespace Vein
{

	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers) {
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* t_Layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, t_Layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* t_Overlay)
	{
		m_Layers.emplace_back(t_Overlay);
	}

	void LayerStack::PopLayer(Layer* t_Layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), t_Layer);
		if (it != m_Layers.begin() + m_LayerInsertIndex)
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* t_Overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), t_Overlay);
		if (it != m_Layers.end())
			m_Layers.erase(it);
	}

}