#include "vnpch.h"
#include "Renderer/OpenGL/OpenGLContext.h"

#include "Core/Logger/Logger.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Vein
{

	OpenGLContext::OpenGLContext(GLFWwindow* t_WindowHandle)
		: m_WindowHandle(t_WindowHandle)
	{
		VN_ASSERT(t_WindowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		VN_ASSERT(status, "Failed to initialize Glad!");

		VN_INFO("OpenGL Info:");
		VN_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		VN_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		VN_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}