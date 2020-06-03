#include "vnpch.h"
#include "Renderer/Buffer.h"

#include "Renderer/Renderer.h"
#include "Renderer/OpenGL/OpenGLBuffer.h"

namespace Vein
{

	VertexBuffer* VertexBuffer::Create(float* t_Vertices, uint32_t t_Size)
	{
		switch (Renderer::GetAPI())
		{
			case Renderer::API::None: VN_ASSERT(false, "No rendering API selected!");
			case Renderer::API::OpenGL:  return new OpenGLVertexBuffer(t_Vertices, t_Size);
		}
		return nullptr;
	}
	
	IndexBuffer* IndexBuffer::Create(uint32_t* t_Indices, uint32_t t_Size)
	{
		switch (Renderer::GetAPI())
		{
			case Renderer::API::None: VN_ASSERT(false, "No rendering API selected!");
			case Renderer::API::OpenGL:  return new OpenGLIndexBuffer(t_Indices, t_Size);
		}
		return nullptr;
	}

}