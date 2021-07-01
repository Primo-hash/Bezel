#include "bezel/Precompiled.h"
#include "bezel/include/App.h"
#include "bezel/include/Input.h"

#include "glad/glad.h"


namespace Bezel {

	App* App::s_Instance = nullptr;

	Bezel::App::App() {
		BZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// Simple test window to check the Window class and children's functionality
		m_Window = std::unique_ptr<Window>(Window::create());

		// Default set of keyboard, mouse and application events running by default
		m_Window->setEventCallback(BZ_BIND_EVENT_FN(App::onEvent));

		// Native GUI instance overlay for the application
		m_ImGuiLayer = new ImGuiLayer();
		pushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::create());

		// Testing with colors
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->setLayout(layout);
		m_VertexArray->addVertexBuffer(vertexBuffer);
		
		// Create indices
		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->setIndexBuffer(indexBuffer);



		// For later abstraction, currently just testing
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;			

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
			}

		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;			

			void main() {
				color = vec4(v_Position + 0.2, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	Bezel::App::~App() {

	}

	/*
		Returns signal to close the referenced application window
		and sets values to represent shutdown.
	*/
	bool App::onWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	void Bezel::App::run() {
		// Simple window test
		while (m_Running) {
			// Draw simple background
			glClearColor(0.5546875, 0.5546875, 0.5546875, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			// For later abstraction
			m_Shader->bind();
			m_VertexArray->bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);


			// Event handling by layer priority
			for (Layer* layer : m_LayerStack) {
				layer->onUpdate();
			}

			// Render GUI
			m_ImGuiLayer->begin();
			for (Layer* layer : m_LayerStack) {
				layer->onImGuiRender();
			}
			m_ImGuiLayer->end();
			m_Window->onUpdate();
		}
	}

	/*
		Uses event dispatcher to handle execution and logging of any event type.
		Checks every frame if the WindowCloseEvent has been requested, and keeps open/closes window.
	*/
	void App::onEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BZ_BIND_EVENT_FN(App::onWindowClose));

		// Handle events in reverse, where overlays have priority
		// Stops iteration if event has been handled
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
		    auto layer = (*--it);
			layer->onEvent(e);
			if (e.handled) { break; }
		}
	}
	
	void App::pushLayer(Layer* layer) {
		m_LayerStack.pushLayer(layer);
		layer->onAttach();
	}

	void App::popLayer(Layer* layer) {
		m_LayerStack.popLayer(layer);
		layer->onDetach();
	}

	void App::pushOverlay(Layer* overlay) {
		m_LayerStack.pushOverlay(overlay);
		overlay->onAttach();
	}

	void App::popOverlay(Layer* overlay) {
		m_LayerStack.popOverlay(overlay);
		overlay->onDetach();
	}

}