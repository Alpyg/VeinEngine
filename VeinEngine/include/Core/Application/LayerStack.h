#pragma once

namespace Vein
{

	class Layer;

	class LayerStack
	{
	public:
		VN_API LayerStack();
		VN_API ~LayerStack();

		VN_API void PushLayer(Layer* t_Layer);
		VN_API void PushOverlay(Layer* t_Overlay);
		VN_API void PopLayer(Layer* t_Layer);
		VN_API void PopOverlay(Layer* t_Overlay);

		VN_API std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		VN_API std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};

}