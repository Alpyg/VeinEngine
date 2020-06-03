#include "vnpch.h"
#include "Core/Application/Application.h"

#include "Core/Logger/Logger.h"
#include "Renderer/Renderer.h"

#include <GLFW/glfw3.h>
#include <gl/GL.h>

namespace Vein
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application(const String& t_WindowName)
	{
		VN_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Scope<Window>(Window::Create({ t_WindowName }));
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* t_Layer)
	{
		m_LayerStack.PushLayer(t_Layer);
		t_Layer->OnAttach();
	}
	
	void Application::PushOverlay(Layer* t_Layer)
	{
		m_LayerStack.PushOverlay(t_Layer);
		t_Layer->OnAttach();
	}

	void Application::OnEvent(Event& t_Event)
	{
		EventDispatcher dispatcher(t_Event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(t_Event);
			if (t_Event.handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			//Time::RecalculateDeltaTime(time);
			
			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack) {
					glEnable(GL_DEPTH_TEST);
					layer->OnUpdate();
					glDisable(GL_DEPTH_TEST);
				}
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& t_Event)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& t_Event)
	{
		if (t_Event.GetWidth() == 0 || t_Event.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		//Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

}