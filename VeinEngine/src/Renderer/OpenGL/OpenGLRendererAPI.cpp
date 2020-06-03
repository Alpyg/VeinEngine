#include "vnpch.h"
#include "Renderer/OpenGL/OpenGLRendererAPI.h"

#include "Renderer/VertexArray.h"

#include <glad/glad.h>

namespace Vein
{

	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t t_X, uint32_t t_Y, uint32_t t_Width, uint32_t t_Height)
	{
		glViewport(t_X, t_Y, t_Width, t_Height);
	}

	void OpenGLRendererAPI::SetClearColor(const Vec4& t_Color)
	{
		glClearColor(t_Color.r, t_Color.g, t_Color.b, t_Color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& t_VertexArray)
	{
		glDrawElements(GL_TRIANGLES, t_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
	}

}