#pragma once

namespace Vein
{

    class VertexArray;

    class VN_API RendererAPI
    {
    public:
        virtual void Init() = 0;
        virtual void SetViewport(uint32_t t_X, uint32_t t_Y, uint32_t t_Width, uint32_t t_Height) = 0;
        virtual void SetClearColor(const Vec4& t_Color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const Ref<VertexArray>& t_VertexArray) = 0;
    };

}