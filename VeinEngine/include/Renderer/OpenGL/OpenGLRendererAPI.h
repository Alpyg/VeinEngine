#pragma once

#include "Renderer/RendererAPI.h"

namespace Vein
{

	class VN_API OpenGLRendererAPI : public RendererAPI
	{
	public:
        virtual void Init() override;
        virtual void SetViewport(uint32_t t_X, uint32_t t_Y, uint32_t t_Width, uint32_t t_Height) override;
        virtual void SetClearColor(const Vec4& t_Color) override;
        virtual void Clear() override;

        virtual void DrawIndexed(const Ref<VertexArray>& t_VertexArray) override;
	};


}