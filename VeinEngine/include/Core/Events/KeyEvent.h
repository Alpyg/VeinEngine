#pragma once

#include "Event.h"

namespace Vein
{

	class VN_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int t_KeyCode)
			: m_KeyCode(t_KeyCode) {}

		int m_KeyCode;
	};

	class VN_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int t_KeyCode, int t_RepeatCount)
			: KeyEvent(t_KeyCode), m_RepeatCount(t_RepeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		String ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent(key=" << m_KeyCode << ", repeats=" << m_RepeatCount << ")";
			return ss.str().c_str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class VN_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int t_KeyCode)
			: KeyEvent(t_KeyCode) {}

		String ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent(key=" << m_KeyCode << ")";
			return ss.str().c_str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class VN_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int t_KeyCode)
			: KeyEvent(t_KeyCode) {}

		String ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent(key=" << m_KeyCode << ")";
			return ss.str().c_str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

}