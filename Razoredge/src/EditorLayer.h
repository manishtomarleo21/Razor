#pragma once

#include "Razor.h"
#include "Panels/SceneHierarchyPanels.h"
#include "Panels/ContentBrowserPanel.h"
#include "Razor/Renderer/EditorCamera.h"


namespace Razor
{

	class EditorLayer : public Layer
	{

	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttack() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);

		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);
		void SaveScene();
		void SaveSceneAs();

		void SerializeScene(Ref<Scene> scene, const std::filesystem::path& path);

		void OnScenePlay();
		void OnSceneStop();

		void OnDuplicateEntity();

		//UI Panel
		void UI_Toolbar();
	private:
		Razor::OrthographicCameraController m_CameraController;


		//Temp
		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;
		Ref<Framebuffer> m_Framebuffer;
		Ref<Texture2D> m_CheckerboardTexture;

		Ref<Scene> m_ActiveScene;
		Ref<Scene> m_EditorScene;
		std::filesystem::path m_EditorScenePath;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		Entity m_HoveredEntity;

		bool m_PrimaryCamera = true;

		EditorCamera m_EditorCamera;

		bool m_ViewportFocused = false, m_ViewportHovered = false;;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBouds[2];


		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

		int m_GizmoType = -1;


		enum class SceneState
		{
			Edit = 0, Play = 1
		};

		SceneState m_SceneState = SceneState::Edit;

		//Panels
		SceneHierarchyPanels m_SceneHierarchyPanel;
		ContentBrowserPanel m_ContentBrowserPanel;

		//Editor resources
		Ref<Texture2D> m_IconPlay, m_IconStop;

		
	};

}