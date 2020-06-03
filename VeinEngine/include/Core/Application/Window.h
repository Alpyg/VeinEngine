#pragma once

#include "Core/Events/Event.h"

namespace Vein
{

	struct WindowProps
	{
		String title;
		unsigned int width;
		unsigned int height;

		WindowProps(
			const String& t_Title = "Vein Engine",
			unsigned t_Width = 1280,
			unsigned t_Height = 720)
			: title(t_Title), width(t_Width), height(t_Height)
		{
		}
	};

	// Interface representing a desktop system based Window
	class VN_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& t_Callback) = 0;
		virtual void SetVSync(bool t_Enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& t_Props = WindowProps());
	};

}