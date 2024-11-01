#pragma once

#include "Razor/Layer.h"
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

	private:
		float m_time;
		bool s_ImGuiInitialized = false;

	};
}