#include <Razor.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include "imgui/imgui.h"

#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public Razor::Layer
{
	public:

	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{

		m_VertexArray.reset(Razor::VertexArray::Create());

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

		m_SquareVA.reset(Razor::VertexArray::Create());


		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};



		Razor::Ref<Razor::VertexBuffer> squareVB;
		squareVB.reset(Razor::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
		{ Razor::ShaderDataType::Float3, "a_Position"}

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

		m_Shader.reset(Razor::Shader::Create(vertexSrc, fragmentSrc));

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

		m_FlatColorShader.reset(Razor::Shader::Create(flatColorShadervertexSrc, flatColorShaderfragmentSrc));

	}

	void OnUpdate(Razor::Timestep ts) override
	{
		//RZ_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliSeconds());

		if (Razor::Input::IsKeyPressed(RZ_KEY_LEFT)) {
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		}
		else if (Razor::Input::IsKeyPressed( RZ_KEY_RIGHT)) {
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}

		if (Razor::Input::IsKeyPressed(RZ_KEY_UP)) {
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		}
		else if (Razor::Input::IsKeyPressed(RZ_KEY_DOWN)) {
			m_CameraPosition.y -= m_CameraMoveSpeed* ts;
		}

		if (Razor::Input::IsKeyPressed(RZ_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Razor::Input::IsKeyPressed(RZ_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;


		
		Razor::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Razor::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Razor::Renderer::BeginScene(m_Camera);

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

		
		Razor::Renderer::Submit(m_Shader, m_VertexArray);

		Razor::Renderer::EndScene();



	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();

	}

	void OnEvent(Razor::Event& event) override
	{
		/*Razor::EventDispatcher dispatcher(event);
		dispatcher.Dispatch< Razor::KeyPressedEvent>(RZ_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));*/
	}

private:
	Razor::Ref<Razor::Shader> m_Shader;
	Razor::Ref<Razor::VertexArray> m_VertexArray;


	Razor::Ref<Razor::Shader> m_FlatColorShader;
	Razor::Ref<Razor::VertexArray> m_SquareVA;

	Razor::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition; 
	float m_CameraMoveSpeed = 5.0f; 

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 10.0f; 

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

};

class Sandbox : public Razor::Application
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		
	}

	~Sandbox() {

	}
};

Razor::Application* Razor::CreateApplication() {
	return new Sandbox();
}