#pragma once

#include "Event.h"
#include <../vendor/spdlog/include/spdlog/fmt/fmt.h>
//#include "Hazel/Events/Event.h"

namespace Razor {

	class RAZOR_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_Width, m_Height;
	};

	class RAZOR_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class RAZOR_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class RAZOR_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class RAZOR_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}
//PERSONAL CHANGES SO IT CAN WORK SOME ERROR

// Define the custom formatter for fmt in the fmt namespace
namespace fmt {

	// Specialize fmt formatter for Razor::WindowResizeEvent
	template <>
	struct formatter<Razor::WindowResizeEvent> {
		// Parses the format string (not needed here, so we return the beginning)
		constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

		// Formats the WindowResizeEvent object
		template <typename FormatContext>
		auto format(const Razor::WindowResizeEvent& event, FormatContext& ctx) {
			// Format it as "WindowResizeEvent: widthxheight"
			return format_to(ctx.out(), "WindowResizeEvent: {}x{}", event.GetWidth(), event.GetHeight());
		}
	};

}