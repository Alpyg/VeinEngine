#include "vnpch.h"
#include "Renderer/Renderer.h"

#include "Renderer/OpenGL/OpenGLRendererAPI.h"

namespace Vein
{

    RendererAPI* Renderer::s_RendererAPI = nullptr;
    Renderer::API Renderer::m_API = API::None;

    void Vein::Renderer::Init(const API& t_API)
    {
        m_API = t_API;
        switch (m_API)
        {
            case API::None:    VN_ASSERT(false, "No rendering API selected!"); return;
            case API::OpenGL:  s_RendererAPI = new OpenGLRendererAPI();
        }
        s_RendererAPI->Init();
    }

    VN_API void Renderer::OnWindowResize(uint32_t t_Width, uint32_t t_Height)
    {
        return s_RendererAPI->SetViewport(0, 0, t_Width, t_Height);
    }

}