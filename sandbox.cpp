/*
	This is currently a testing ground for Bezel Engine features
*/
#include "bezel/Bezel.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>

/*
	An example Layer class that draws a GUI
*/
class ExampleLayer : public Bezel::Layer {
private:
	std::shared_ptr<Bezel::Shader> m_Shader;
	std::shared_ptr<Bezel::VertexArray> m_VertexArray;
	

	std::shared_ptr<Bezel::Shader> m_SquareShader;
	std::shared_ptr<Bezel::VertexArray> m_SquareVA;

	Bezel::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
public:
	ExampleLayer() : Layer("Layer"), m_Camera(-3.2f, 3.2f, -1.8f, 1.8f), m_CameraPosition(0.0f) {
		m_VertexArray.reset(Bezel::VertexArray::create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Bezel::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Bezel::VertexBuffer::create(vertices, sizeof(vertices)));
		Bezel::BufferLayout layout = {
			{ Bezel::ShaderDataType::Float3, "a_Position" },
			{ Bezel::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->setLayout(layout);
		m_VertexArray->addVertexBuffer(vertexBuffer);

		// Create indices
		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Bezel::IndexBuffer> indexBuffer;
		indexBuffer.reset(Bezel::IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->setIndexBuffer(indexBuffer);

		m_SquareVA.reset(Bezel::VertexArray::create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Bezel::VertexBuffer> squareVB;
		squareVB.reset(Bezel::VertexBuffer::create(squareVertices, sizeof(squareVertices)));
		squareVB->setLayout({
			{ Bezel::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->addVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Bezel::IndexBuffer> squareIB;
		squareIB.reset(Bezel::IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
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

		m_Shader.reset(new Bezel::Shader(vertexSrc, fragmentSrc));
	
		// SQUARE SHADER PROGRAM

		std::string squareShaderVertexSrc = R"(
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

		std::string squareShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_SquareShader.reset(new Bezel::Shader(squareShaderVertexSrc, squareShaderFragmentSrc));

	}

	void onUpdate(Bezel::Timestep ts) override {

		if (Bezel::Input::isKeyPressed(BZ_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Bezel::Input::isKeyPressed(BZ_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Bezel::Input::isKeyPressed(BZ_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Bezel::Input::isKeyPressed(BZ_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Bezel::Input::isKeyPressed(BZ_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Bezel::Input::isKeyPressed(BZ_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		// Draw simple background
		Bezel::RenderCommand::setClearColor({ 0.5546875, 0.5546875, 0.5546875, 1 });
		Bezel::RenderCommand::clear();

		// Manual setup of camera position
		m_Camera.setPosition(m_CameraPosition);
		m_Camera.setRotation(m_CameraRotation);

		// New scene tied to app camera
		Bezel::Renderer::beginScene(m_Camera);


		// Submit our triangle with how to draw then what to draw
		// in the scene
		//Bezel::Renderer::submit(m_Shader, m_VertexArray);
		
		
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f)); // scales down on transformation

		for (int y = 0; y < 20; y++)		// Create square of 20 squares
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f); // Changes x and y position for each square
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Bezel::Renderer::submit(m_SquareShader, m_SquareVA, transform);		// Submit square
			}
		}

		// Done submitting
		Bezel::Renderer::endScene();

	}

	virtual void onImGuiRender() override {
	
	}


	void onEvent(Bezel::Event& event) override {
		// Logs keystrokes and when TAB key is pressed using Event system
	}

};

/*
	An example Overlay class
*/
class ExampleOverlay : public Bezel::Layer {
public:
	ExampleOverlay() : Layer("Overlay") {}

	void onUpdate(Bezel::Timestep ts) override {
		BZ_CLIENT_INFO("Overlay::Update");
	}

	void onEvent(Bezel::Event& event) override {
		BZ_CLIENT_TRACE("{0}", event);
	}

};

/*
	An example application class
*/
class SandBox : public Bezel::App {
public:
	SandBox() {
		pushLayer(new ExampleLayer());	// Pushes example overlay with a GUI
	}

	~SandBox() {

	}
};

/*
	Returns a new application sandbox defined by Bezel.
*/
Bezel::App* Bezel::createApp() {
	return new SandBox();
}
