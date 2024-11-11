//#include "rzpch.h"
#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include "Platform/OpenGL/OpenGLShader.h"



Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttack()
{
	m_CheckerboardTexture = Razor::Texture2D::Create("assets/textures/checkerboard.png");
	//m_SpriteSheet = Razor::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");

	
	

	m_CameraController.SetZoomLevel(5.0f);
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Razor::Timestep ts)
{
	RZ_PROFILE_FUNCTION();

	RZ_PROFILE_SCOPE("CameraController::OnUpdate");
	m_CameraController.OnUpdate(ts);

	//Renderer
	Razor::Renderer2D::ResetStats();

	RZ_PROFILE_SCOPE("Renderer Prep!");
	

	Razor::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Razor::RenderCommand::Clear();


	//std::dynamic_pointer_cast<Razor::OpenGLShader>(m_FlatColorShader)->Bind();
	//std::dynamic_pointer_cast<Razor::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
	 
	
	//Razor::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));


	
	static float rotation = 0.0f;
	rotation += ts * 20.0f;

	RZ_PROFILE_SCOPE("Renderer Draw!");

	Razor::Renderer2D::BeginScene(m_CameraController.GetCamera());

	//For rotation use glm::radians

	Razor::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	//Razor::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
	Razor::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	//Razor::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
	Razor::Renderer2D::DrawRotatedQuad({ -0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f }, glm::radians(rotation), m_CheckerboardTexture, 20.0f);
	//Razor::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f, glm::vec4(1.0f, 0.9f, 0.9f, 1.0f));
	//Razor::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, glm::radians(45.0f), m_CheckerboardTexture, 10.0f, glm::vec4(1.0f, 0.9f, 0.9f, 1.0f));

	Razor::Renderer2D::EndScene();

	Razor::Renderer2D::BeginScene(m_CameraController.GetCamera());

	for (float y = -5.0f; y < 5.0f; y += 0.5f)
	{
		for (float x = -5.0f; x < 5.0f; x += 0.5f)
		{
			glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 1.0f };
			Razor::Renderer2D::DrawQuad({ x,y }, { 0.45f, 0.45f }, color);
		}
	}

	Razor::Renderer2D::EndScene();



	Razor::Renderer2D::EndScene();
	

	// currently for reversing the texture or image using glsl update here is other method in case glsl cause trouble
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
} 

void Sandbox2D::OnImGuiRender()
{
	RZ_PROFILE_FUNCTION();

	//----our Window cODE important

	ImGui::Begin("Settings");

	auto stats = Razor::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats: ");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());


	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	//ImGui::Image((void*)m_CheckerboardTexture->GetRendererID(), ImVec2{64.0f, 64.0f});

	// if having the images rendered upside down in ImGui, add ImVec2{ 0,1 }, 
	// ImVec2{1,0} to the parameters of ImGui::Image to change the UV's of the image

	ImGui::End();


}

void Sandbox2D::OnEvent(Razor::Event& e)
{
	m_CameraController.OnEvent(e);

}
