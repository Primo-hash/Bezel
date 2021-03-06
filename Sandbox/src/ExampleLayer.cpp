#include "include/layers/ExampleLayer.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


ExampleLayer::ExampleLayer() : Layer("Layer"), m_CameraController(1600.0f / 900.0f) {
	m_VertexArray = Bezel::VertexArray::create();

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};

	Bezel::Ref<Bezel::VertexBuffer> vertexBuffer = Bezel::VertexBuffer::create(vertices, sizeof(vertices));
	Bezel::BufferLayout layout = {
		{ Bezel::ShaderDataType::Float3, "a_Position" },
		{ Bezel::ShaderDataType::Float4, "a_Color" }
	};

	vertexBuffer->setLayout(layout);
	m_VertexArray->addVertexBuffer(vertexBuffer);

	// Create indices
	uint32_t indices[3] = { 0, 1, 2 };
	Bezel::Ref<Bezel::IndexBuffer> indexBuffer = Bezel::IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t));
	m_VertexArray->setIndexBuffer(indexBuffer);

	m_SquareVA = Bezel::VertexArray::create();

	// coords, texcoords
	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	Bezel::Ref<Bezel::VertexBuffer> squareVB = Bezel::VertexBuffer::create(squareVertices, sizeof(squareVertices));
	squareVB->setLayout({
		{ Bezel::ShaderDataType::Float3, "a_Position" },
		{ Bezel::ShaderDataType::Float2, "a_TexCoord" }
		});
	m_SquareVA->addVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Bezel::Ref<Bezel::IndexBuffer> squareIB = Bezel::IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVA->setIndexBuffer(squareIB);

	// TRIANGLE SHADER PROGRAM

	// For later abstraction, currently just testing
	std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			

			void main() {
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

			void main() {
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

	m_Shader = Bezel::Shader::create("VertexPosColor", vertexSrc, fragmentSrc);

	// SQUARE SHADER PROGRAM

	std::string flatColorShaderVertexSrc = R"(
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

	std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

	m_FlatColorShader = Bezel::Shader::create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

	// ADD TEXTURE SHADER PROGRAM USING SHADER FILE TO SHADER LIB
	auto textureShader = m_ShaderLibrary.load("assets/shaders/Texture.glsl");

	m_Texture = Bezel::Texture2D::create("assets/textures/clouds.png");
	m_CloudBerryTexture = Bezel::Texture2D::create("assets/textures/cloudberry.png");

	textureShader->bind();
	textureShader->setInt("u_Texture", 0);
}

ExampleLayer::~ExampleLayer() {

}

void ExampleLayer::onUpdate(Bezel::Timestep ts) {

	// Camera events and functions to be run in game loop
	m_CameraController.onUpdate(ts);

	// Draw simple background
	Bezel::RenderCommand::setClearColor({ 0.5546875, 0.5546875, 0.5546875, 1 });
	Bezel::RenderCommand::clear();

	// New scene tied to app camera
	Bezel::Renderer::beginScene(m_CameraController.getCamera());


	// Submit our triangle with how to draw then what to draw
	// in the scene
	//Bezel::Renderer::submit(m_Shader, m_VertexArray);


	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f)); // scales down on transformation

	m_FlatColorShader->bind();
	m_FlatColorShader->setFloat3("u_Color", m_SquareColor);

	for (int y = 0; y < 20; y++)		// Create square of 20 squares
	{
		for (int x = 0; x < 20; x++)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f); // Changes x and y position for each square
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			Bezel::Renderer::submit(m_FlatColorShader, m_SquareVA, transform);		// Submit square
		}
	}

	auto textureShader = m_ShaderLibrary.get("Texture");	// Retrieves texture from library

	m_Texture->bind();
	Bezel::Renderer::submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	m_CloudBerryTexture->bind();
	Bezel::Renderer::submit(textureShader, m_SquareVA, glm::scale(glm::mat4(0.5f), glm::vec3(0.5f)));


	// Done submitting
	Bezel::Renderer::endScene();

}

void ExampleLayer::onImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

/*
	For recording and handling events as they happen on this layer,
	Needs reference to current layer event object
*/
void ExampleLayer::onEvent(Bezel::Event& e) {
	m_CameraController.onEvent(e);
}