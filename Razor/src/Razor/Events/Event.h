#pragma once

#include "rzpch.h"
#include <spdlog/fmt/ostr.h>
#include "../core.h"



namespace Razor {

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved, AppTick, AppUpdate, AppRender, KeyPressed,
		KeyReleased, MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled, 
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyBoard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4),

	};

	#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

	#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class RAZOR_API Event{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName();}

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	protected:
		bool m_Handled = false;
	};


	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		// F will be deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled |= func(static_cast<T&>(m_Event));
				
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}


}

// namespace Razor

// Custom formatter specialization for Razor::Event

//its custom foramatter myCode
template <>
struct fmt::formatter<Razor::Event> {
	constexpr auto parse(fmt::format_parse_context& ctx) -> decltype(ctx.begin()) {
		return ctx.begin();
	}

	template <typename FormatContext>
	auto format(const Razor::Event& event, FormatContext& ctx) -> decltype(ctx.out()) {
		// Use the Event's ToString method or customize this as needed
		return fmt::format_to(ctx.out(), "{}", event.ToString());
	}
};
