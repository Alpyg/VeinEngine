#include "vnpch.h"
#include "Renderer/OpenGL/OpenGLTexture.h"

#include "Core/Logger/Logger.h"

#include <stb_image.h>
#include <glad/glad.h>

namespace Vein
{

	OpenGLTexture2D::OpenGLTexture2D(const String& t_Path, const TextureType& t_Type)
		: m_Path(t_Path)
		, m_Type(t_Type)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(0);
		stbi_uc* data = stbi_load(m_Path.c_str(), &width, &height, &channels, 0);
		VN_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t t_Slot) const
	{
		glBindTextureUnit(t_Slot, m_RendererID);
	}
}