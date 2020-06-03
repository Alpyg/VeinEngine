#pragma once

#include "Renderer/Texture.h"

namespace Vein
{

	class OpenGLTexture2D : public Texture2D
	{
	public:
		VN_API OpenGLTexture2D(const String& t_Path, const TextureType& t_Type);
		VN_API virtual ~OpenGLTexture2D();

		VN_API virtual String GetPath() const override { return m_Path; }
		VN_API virtual uint32_t GetWidth() const override { return m_Width; }
		VN_API virtual uint32_t GetHeight() const override { return m_Height; }
		VN_API virtual TextureType GetType() const override { return m_Type; }

		VN_API virtual void Bind(uint32_t slot = 0) const override;
	private:
		String m_Path;
		uint32_t m_RendererID;
		uint32_t m_Width, m_Height;
		TextureType m_Type;
	};

}