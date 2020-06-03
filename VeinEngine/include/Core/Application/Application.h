#pragma once

#include "Core/Application/Layer.h"
#include "Core/Application/LayerStack.h"
#include "Core/Application/Window.h"
#include "Core/Events/Event.h"
#include "Core/Events/ApplicationEvent.h"

#include "Core/String/String.h"

namespace Vein
{

	class Application
	{
	public:
		VN_API Application(const String& t_WindowName);
		VN_API virtual ~Application();

		VN_API void Run();

		VN_API void OnEvent(Event& t_Event);

		VN_API void PushLayer(Layer* t_Layer);
		VN_API void PushOverlay(Layer* t_Layer);

		VN_API inline Window& GetWindow() { return *m_Window.get(); }

		VN_API inline static Application& Get() { return *s_Instance; }
	private:
		VN_API bool OnWindowClose(WindowCloseEvent& t_Event);
		VN_API bool OnWindowResize(WindowResizeEvent& t_Event);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
	private:
		VN_API static Application* s_Instance;
	};

	Application* CreateApplication();

}