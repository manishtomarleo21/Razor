#include <Razor.h>
//--------ENtry point-------

#include <Razor/Core/EntryPoint.h>
//--------------------


#include "Platform/OpenGL/OpenGLShader.h"
#include "imgui/imgui.h"

#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Sandbox2D.h"


class ExampleLayer : public Razor::Layer
{
	public:	

	ExampleLayer()
		:Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{

		m_VertexArray = Razor::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		};

		Razor::Ref<Razor::VertexBuffer> vertexBuffer;

		vertexBuffer.reset(Razor::VertexBuffer::Create(vertices, sizeof(vertices)));

		Razor::BufferLayout layout = {
			{ Razor::ShaderDataType::Float3, "a_Position"},
			{ Razor::ShaderDataType::Float4, "a_Color"}

		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);


		uint32_t indices[3] = { 0, 1, 2 };
		Razor::Ref<Razor::IndexBuffer> indexBuffer;

		indexBuffer.reset(Razor::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = Razor::VertexArray::Create();


		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};



		Razor::Ref<Razor::VertexBuffer> squareVB;
		squareVB.reset(Razor::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
		{ Razor::ShaderDataType::Float3, "a_Position"},
		{ Razor::ShaderDataType::Float2, "a_TexCoord"}

			});

		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squarIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Razor::Ref<Razor::IndexBuffer> squareIB;
		squareIB.reset(Razor::IndexBuffer::Create(squarIndices, sizeof(squarIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(

			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		
		)";

		std::string fragmentSrc = R"(

			#version 330 core
			
			layout(location = 0) out vec4 color;


			in vec3 v_Position;
			in vec4 v_Color;


			void main()
			{
				
				color = vec4(0.8, 0.2, 0.3, 1.0);
				color = v_Color;
			}
		
		)";

		m_Shader = Razor::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShadervertexSrc = R"(

			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
		
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			
			out vec3 v_Position;
			

			void main()
			{
				v_Position = a_Position;
		
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		
		)";

		std::string flatColorShaderfragmentSrc = R"(

			#version 330 core
			
			layout(location = 0) out vec4 color;


			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				
				color = vec4(u_Color, 1.0);
			
			}
		
		)";

		m_FlatColorShader = Razor::Shader::Create( "FlatColor", flatColorShadervertexSrc, flatColorShaderfragmentSrc);

		
		//m_TextureShader = Razor::Shader::Create("assets/shaders/Texture.glsl");
		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Razor::Texture2D::Create("assets/textures/checkerboard.png");
		m_LogoTexture = Razor::Texture2D::Create("assets/textures/logo.png");
		

		std::dynamic_pointer_cast<Razor::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Razor::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Razor::Timestep ts) override
	{
		//RZ_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliSeconds());

		//Update
		m_CameraController.OnUpdate(ts);

		//Renderer
		Razor::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Razor::RenderCommand::Clear();

		
		Razor::Renderer::BeginScene(m_CameraController.GetCamera());

		//glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	
		std::dynamic_pointer_cast<Razor::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Razor::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Razor::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);

			}

		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();

		Razor::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_LogoTexture->Bind();

		Razor::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//Triangle
		//Razor::Renderer::Submit(m_Shader, m_VertexArray);

		Razor::Renderer::EndScene();



	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();

	}

	void OnEvent(Razor::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	Razor::ShaderLibrary m_ShaderLibrary;
	Razor::Ref<Razor::Shader> m_Shader;
	Razor::Ref<Razor::VertexArray> m_VertexArray;


	Razor::Ref<Razor::Shader> m_FlatColorShader;
	//Razor::Ref<Razor::Shader> m_FlatColorShader, m_TextureShader;
	Razor::Ref<Razor::VertexArray> m_SquareVA;

	Razor::Ref<Razor::Texture2D> m_Texture, m_LogoTexture;

	Razor::OrthographicCameraController m_CameraController;
	//glm::vec3 m_CameraPosition; 
	//float m_CameraMoveSpeed = 5.0f; 

	//float m_CameraRotation = 0.0f;
	//float m_CameraRotationSpeed = 10.0f; 

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

};

class Sandbox : public Razor::Application
{
public:
	Sandbox() {
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox() {

	}
};

Razor::Application* Razor::CreateApplication() {
	return new Sandbox();
}