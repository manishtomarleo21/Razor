#pragma once

#include "Razor/Core/core.h"
#include "Razor/Core/Timestep.h"	
#include "Razor/Events/Event.h"

namespace Razor {
	
	class RAZOR_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttack() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(Timestep ts) {};
		virtual void OnImGuiRender() {};
		virtual void OnEvent(Event& event) {};

		const std::string& GetName() const { return m_DebugName; }

		std::string m_DebugName;
	protected:
	};
}
