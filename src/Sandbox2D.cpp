#include "Sandbox2D.h"
#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1600.0f / 900.0f) {

}

void Sandbox2D::onAttach() {
	m_CloudTexture = Bezel::Texture2D::create("assets/textures/clouds.png");
}

void Sandbox2D::onDetach() {
}

void Sandbox2D::onUpdate(Bezel::Timestep ts) {
	// Update
	m_CameraController.onUpdate(ts);

	// Render
	Bezel::RenderCommand::setClearColor({ 0.5546875, 0.5546875, 0.5546875, 1 });
	Bezel::RenderCommand::clear();

	Bezel::Renderer2D::beginScene(m_CameraController.getCamera());
	// Testing Quad and textures
	Bezel::Renderer2D::drawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Bezel::Renderer2D::drawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);
	Bezel::Renderer2D::drawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CloudTexture);
	Bezel::Renderer2D::endScene();
}

void Sandbox2D::onImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::onEvent(Bezel::Event& e) {
	m_CameraController.onEvent(e);
}