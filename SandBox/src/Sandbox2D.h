#pragma once

#include "Razor.h"

#include "ParticleSystem.h"

class Sandbox2D : public Razor::Layer
{

public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttack() override;
	virtual void OnDetach() override;

	void OnUpdate(Razor::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Razor::Event& e) override;
private:
	Razor::OrthographicCameraController m_CameraController;


	//Temp
	Razor::Ref<Razor::VertexArray> m_SquareVA;
	Razor::Ref<Razor::Shader> m_FlatColorShader;


	Razor::Ref<Razor::Texture2D> m_CheckerboardTexture;
	Razor::Ref<Razor::Texture2D> m_SpriteSheet;
	Razor::Ref<Razor::SubTexture2D> m_TextureStairs, m_TextureBarrel;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	
	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;

	uint32_t m_MapWidth, m_MapHeight;
	std::unordered_map<char, Razor::Ref<Razor::SubTexture2D>> s_TexureMap;
};
 