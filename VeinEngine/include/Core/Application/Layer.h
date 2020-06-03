#pragma once

#include "Core/Core.h"
#include "Core/Events/Event.h"

namespace Vein
{

	class Layer
	{
	public:
		VN_API Layer(const String& t_Name = "Layer") : m_DebugName(t_Name) {};
		VN_API virtual ~Layer() {};

		VN_API virtual void OnAttach() = 0;
		VN_API virtual void OnDetach() = 0;
		VN_API virtual void OnUpdate() = 0;
		VN_API virtual void OnEvent(Event& t_Event) = 0;

		VN_API inline const String& GetName() const { return m_DebugName; }
	protected:
		String m_DebugName;
	};

}