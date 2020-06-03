#pragma once

#include "Core/String/String.h"

namespace Vein
{

	enum class TextureType {
		NONE = 0,
		DIFFUSE, SPECULIAR, AMBIENT, EMISSIVE, HEIGHT, NORMALS,
		SHININESS, OPACITY, DISPLACEMENT, LIGHTMAP, REFLECTION
	};

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual String GetPath() const = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual TextureType GetType() const = 0;

		virtual void Bind(uint32_t t_Slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	};

}