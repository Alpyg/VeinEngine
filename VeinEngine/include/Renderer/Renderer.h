#pragma once

#include "Renderer/RendererAPI.h"
#include "Core/Logger/Logger.h"

namespace Vein
{

    class Renderer
    {
    public:
        enum class API {
            None = 0, OpenGL
        };

		VN_API static void Init(const API& t_API);

		VN_API inline static void SetViewport(uint32_t t_X, uint32_t t_Y, uint32_t t_Width, uint32_t t_Height)
		{
			VN_ASSERT(s_RendererAPI, "Renderer not initialized!")
			s_RendererAPI->SetViewport(t_X, t_Y, t_Width, t_Height);
		}

		VN_API inline static void SetClearColor(const Vec4& t_Color)
		{
			VN_ASSERT(s_RendererAPI, "Renderer not initialized!")
			s_RendererAPI->SetClearColor(t_Color);
		}

		VN_API inline static void Clear()
		{
			VN_ASSERT(s_RendererAPI, "Renderer not initialized!")
			s_RendererAPI->Clear();
		}

		VN_API inline static void DrawIndexed(const Ref<VertexArray>& t_VertexArray)
		{
			VN_ASSERT(s_RendererAPI, "Renderer not initialized!")
			s_RendererAPI->DrawIndexed(t_VertexArray);
		}

		VN_API inline static API GetAPI() { return m_API; }

		VN_API static void OnWindowResize(uint32_t t_Width, uint32_t t_Height);
    private:
        static RendererAPI* s_RendererAPI;
		static API m_API;
    };

}