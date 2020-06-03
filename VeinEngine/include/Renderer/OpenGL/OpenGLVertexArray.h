#pragma once

#include "Renderer/VertexArray.h"

namespace Vein
{

	class OpenGLVertexArray : public VertexArray
	{
	public:
		VN_API OpenGLVertexArray();
		VN_API virtual ~OpenGLVertexArray();

		VN_API virtual void Bind() const override;
		VN_API virtual void Unbind() const override;

		VN_API virtual void AddVertexBuffer(const Ref<VertexBuffer>& t_VertexBuffer) override;
		VN_API virtual void SetIndexBuffer(const Ref<IndexBuffer>& t_IndexBuffer) override;

		VN_API virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		VN_API virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndexOffset = 0;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};

}