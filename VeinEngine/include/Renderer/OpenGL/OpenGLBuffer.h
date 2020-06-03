#pragma once

#include "Renderer/Buffer.h"

namespace Vein
{

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		VN_API OpenGLVertexBuffer(float* t_Vertices, uint32_t t_Size);
		VN_API virtual ~OpenGLVertexBuffer();

		VN_API virtual void Bind() const override;
		VN_API virtual void Unbind() const override;

		VN_API virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		VN_API virtual void SetLayout(const BufferLayout& t_Layout) override { m_Layout = t_Layout; }
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		VN_API OpenGLIndexBuffer(uint32_t* t_Indices, uint32_t t_Count);
		VN_API virtual ~OpenGLIndexBuffer();

		VN_API virtual void Bind() const;
		VN_API virtual void Unbind() const;

		VN_API virtual uint32_t GetCount() const { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

}