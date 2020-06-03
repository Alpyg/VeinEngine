#pragma once

#include "Core/String/String.h"

namespace Vein
{

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual const String& GetName() const = 0;
	};

}