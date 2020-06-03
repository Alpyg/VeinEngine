#pragma once

#include "Core/String/String.h"
#include "Core/Logger/Logger.h"

namespace Vein
{

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType t_Type)
	{
		switch (t_Type)
		{
			case ShaderDataType::Float:    return 4;
			case ShaderDataType::Float2:   return 4 * 2;
			case ShaderDataType::Float3:   return 4 * 3;
			case ShaderDataType::Float4:   return 4 * 4;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;
			case ShaderDataType::Int4:     return 4 * 4;
			case ShaderDataType::Bool:     return 1;
		}

		VN_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		String name;
		ShaderDataType type;
		uint32_t size;
		uint32_t offset;
		bool normalized;

		BufferElement() {}

		BufferElement(ShaderDataType t_Type, const String& t_Name, bool t_Normalized = false)
			: name(t_Name), type(t_Type), size(ShaderDataTypeSize(t_Type)), offset(0), normalized(t_Normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (type)
			{
				case ShaderDataType::Float:   return 1;
				case ShaderDataType::Float2:  return 2;
				case ShaderDataType::Float3:  return 3;
				case ShaderDataType::Float4:  return 4;
				case ShaderDataType::Mat3:    return 3 * 3;
				case ShaderDataType::Mat4:    return 4 * 4;
				case ShaderDataType::Int:     return 1;
				case ShaderDataType::Int2:    return 2;
				case ShaderDataType::Int3:    return 3;
				case ShaderDataType::Int4:    return 4;
				case ShaderDataType::Bool:    return 1;
			}

			VN_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		VN_API BufferLayout() {}

		VN_API BufferLayout(const std::initializer_list<BufferElement>& t_Elements)
			: m_Elements(t_Elements)
		{
			CalculateOffsetsAndStride();
		}

		VN_API inline uint32_t GetStride() const { return m_Stride; }
		VN_API inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		VN_API std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		VN_API std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		VN_API std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		VN_API std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		VN_API void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.offset = offset;
				offset += element.size;
				m_Stride += element.size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class VN_API VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& t_Layout) = 0;

		static VertexBuffer* Create(float* t_Vertices, uint32_t t_Size);
	};

	class VN_API IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* t_Indices, uint32_t t_Size);
	};

}