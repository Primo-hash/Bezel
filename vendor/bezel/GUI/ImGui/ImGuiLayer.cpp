#include "bezel/Precompiled.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"	// ImGui Renderer for OpenGL
#include "GLFW/glfw3.h"	// Temporary hack before later abstraction
#include "GL/glew.h"

#include "shader.h"
#include "file_manager.h"

#include "bezel/include/App.h"

#define PI 3.14159265358979323846

// TEMPORARY
void create_triangle(unsigned int& vbo, unsigned int& vao, unsigned int& ebo)
{

	// create the triangle
	float triangle_vertices[] = {
		0.0f, 0.25f, 0.0f,	// position vertex 1
		1.0f, 1.0f, 1.0f,	 // color vertex 1
		0.25f, -0.25f, 0.0f,  // position vertex 1
		1.0f, 1.0f, 1.0f,	 // color vertex 1
		-0.25f, -0.25f, 0.0f, // position vertex 1
		1.0f, 1.0f, 1.0f,	 // color vertex 1
	};
	unsigned int triangle_indices[] = {
		0, 1, 2 };
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangle_indices), triangle_indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

namespace Bezel {

	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {
	
	}

	ImGuiLayer::~ImGuiLayer() {

	}

	void ImGuiLayer::onAttach() {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TEMPORARY
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		bool err = glewInit() != GLEW_OK;
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::onDetach() {

	}

	void ImGuiLayer::onUpdate() {
		ImGuiIO& io = ImGui::GetIO();
		App& app = App::get();
		io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		static bool show = true;

		bool created = false;

		Shader triangle_shader;

		// create our geometries
		unsigned int vbo, vao, ebo;
		create_triangle(vbo, vao, ebo);
		created = true;

		// init shader
		triangle_shader.init(FileManager::read("assets/shader.vs"), FileManager::read("assets/shader.fs"));


		ImGui::SetNextWindowSize(ImVec2((float)100.0, (float)100.0));
		// feed inputs to dear imgui, start new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		//create_triangle(vbo, vao, ebo);

		// rendering our geometries
		triangle_shader.use();
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// render your GUI
		ImGui::Begin("Triangle Position/Color");
		static float rotation = 0.0;
		ImGui::SliderFloat("rotation", &rotation, 0, 2 * PI);
		static float translation[] = { 0.0, 0.0 };
		ImGui::SliderFloat2("position", translation, -1.0, 1.0);
		static float color[4] = { 1.0f,0.0f,1.0f,1.0f };
		// pass the parameters to the shader
		triangle_shader.setUniform("rotation", rotation);
		triangle_shader.setUniform("translation", translation[0], translation[1]);
		// color picker
		ImGui::ColorEdit3("color", color);
		// multiply triangle's color with this color
		triangle_shader.setUniform("color", color[0], color[1], color[2]);
		ImGui::End();


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::onEvent(Event& event) {

	}

}