#pragma once

#include "Renderer/Context.h"

struct GLFWwindow;

namespace Vein
{

	class VN_API OpenGLContext : public Context
	{
	public:
		OpenGLContext(GLFWwindow* t_WindowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}