#pragma once

#include "Razor/Core/Layer.h"
#include "Razor/Events/ApplicationEvent.h"
#include "Razor/Events/KeyEvent.h"
#include "Razor/Events/MouseEvent.h"

namespace Razor
{
	class RAZOR_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		

		virtual void OnAttack()  override;
		virtual void OnDetach()	 override;
		virtual void OnImGuiRender() override;
		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();
	private:
		float m_time = 0.0f;
		bool s_ImGuiInitialized = false;
		bool m_BlockEvents = true;

	};
}