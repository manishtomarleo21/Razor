#pragma once

#include "core.h"
#include "Razor\Events\Event.h"
#include "Razor\Events\ApplicationEvent.h"
#include "Razor/Core/Window.h"

#include "Razor/Core/LayerStack.h"
#include "Razor/ImGui/ImGuiLayer.h"
#include "Razor/Core/Timestep.h"


#include "Razor/Renderer/Shader.h"
#include "Razor/Renderer/Buffer.h"
#include "Razor/Renderer/VertexArray.h"

#include "Razor/Renderer/OrthographicCamera.h"

namespace Razor {

	class RAZOR_API Application
	{
	public:
		Application(const std::string& name = "Razor App");
		virtual ~Application() {};

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);


		inline Window& GetWindow() { return *m_Window; }

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
		
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack; 
		float m_LastFrameTime = 0.0f;
	
	private:
		static Application* s_Instance;
;	};

	static Application* CreateApplication();

	
}

