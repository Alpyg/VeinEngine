#pragma once

#include "Event.h"

namespace Vein
{

	class VN_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float t_X, float t_Y, float t_LastX, float t_LastY)
			: m_X(t_X), m_Y(t_Y), m_LastX(t_LastX), m_LastY(t_LastY) {}

		inline float GetX() const { return m_X; }
		inline float GetY() const { return m_Y; }
		inline float GetLastX() const { return m_LastX; }
		inline float GetLastY() const { return m_LastY; }

		String ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent(x=" << m_X << ", y=" << m_Y << "lastX=" << m_LastX << ", lastY=" << m_LastY << ")";
			return ss.str().c_str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_X, m_Y, m_LastX, m_LastY;
	};

	class VN_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float t_OffsetX, float t_OffsetY)
			: m_OffsetX(t_OffsetX), m_OffsetY(t_OffsetY) {}

		inline float GetXOffset() const { return m_OffsetX; }
		inline float GetYOffset() const { return m_OffsetY; }

		String ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent(x_offset=" << GetXOffset() << ", y_offset=" << GetYOffset() << ")";
			return ss.str().c_str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_OffsetX, m_OffsetY;
	};

	class VN_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int t_Button)
			: m_Button(t_Button) {}

		int m_Button;
	};

	class VN_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int t_Button)
			: MouseButtonEvent(t_Button) {}

		String ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent(key=" << m_Button << ")";
			return ss.str().c_str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class VN_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int t_Button)
			: MouseButtonEvent(t_Button) {}

		String ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent(key=" << m_Button << ")";
			return ss.str().c_str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}