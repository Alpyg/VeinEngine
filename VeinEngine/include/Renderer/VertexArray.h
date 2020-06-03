#pragma once

#include "Renderer/Buffer.h"

namespace Vein
{

	class VN_API VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& t_VertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& t_IndexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};

}