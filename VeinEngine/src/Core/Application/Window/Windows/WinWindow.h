#pragma once

#include "Core/Application/Window.h"
#include "Renderer/Context.h"

#include <GLFW/glfw3.h>

namespace Vein
{

	class VN_API WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& t_Props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.width; }
		inline unsigned int GetHeight() const override { return m_Data.height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& t_Callback) override { m_Data.EventCallback = t_Callback; }
		void SetVSync(bool t_Enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProps& t_Props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		Context* m_Context;

		struct WindowData
		{
			String title;
			unsigned int width, height;
			float lastX = 0, lastY = 0;
			bool vSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}
