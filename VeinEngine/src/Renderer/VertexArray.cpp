#include "vnpch.h"
#include "Renderer/VertexArray.h"

#include "Renderer/Renderer.h"
#include "Renderer/OpenGL/OpenGLVertexArray.h"

namespace Vein
{

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case Renderer::API::None:    VN_ASSERT(false, "No rendering API selected!");
			case Renderer::API::OpenGL:  return new OpenGLVertexArray();
		}
		return nullptr;
	}

}