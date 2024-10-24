#pragma once


#include "Razor/Events/Event.h"
//#include "Razor/Core/KeyCodes.h"



namespace Razor {

	class RAZOR_API keyEvent : public Event {
	public:
		inline int GetKeyCode() const {return m_KeyCode;}

			EVENT_CLASS_CATEGORY(EventCategoryKeyBoard | EventCategoryInput)

	protected:
		//KeyEvent(const KeyCode keycode)
		keyEvent(int keycode)
			: m_KeyCode(keycode) {}

		int m_KeyCode;
	};

	class RAZOR_API KeyPressedEvent : public keyEvent
	{
	public:
		//KeyPressedEvent(const KeyCode keycode, bool isRepeat = false)
		KeyPressedEvent(int keycode, int repeatCount)
			: keyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (repeat = " << m_RepeatCount << ")";
			return ss.str();
		}
		
		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class RAZOR_API KeyReleasedEvent : public keyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: keyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	/*class RAZOR_API KeyTypedEvent : public keyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: keyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};*/
}

