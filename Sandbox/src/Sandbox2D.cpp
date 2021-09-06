#include "include/layers/Sandbox2D.h"
#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>


/*
	The timer class is an insource class used to profile engine performance 
	on a function by function basis. Profiling in this case could be the collection of
	data for each function on a frame by frame basis in game loop.
	TODO: Move to engine
*/
template<typename Fn>
class Timer {
private:
	const char* m_Name;
	Fn m_Func;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
public:
	Timer(const char* name, Fn&& func) : m_Name(name), m_Func(func), m_Stopped(false) {
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer() {
		if (!m_Stopped) { Stop(); }
	}

	void Stop() {
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;

		// Store result in millisecond fractions
		float duration = (end - start) * 0.001f;
		m_Func({ m_Name, duration });
	}
};

//	Macro for setting up a timer profile with a name
#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })


Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1600.0f / 900.0f) {

}

void Sandbox2D::onAttach() {
	m_CloudTexture = Bezel::Texture2D::create("assets/textures/clouds.png");
}

void Sandbox2D::onDetach() {
}

void Sandbox2D::onUpdate(Bezel::Timestep ts) {
	PROFILE_SCOPE("Sandbox2D::onUpdate");

	// Update
	{
		PROFILE_SCOPE("CameraController::onUpdate");
		m_CameraController.onUpdate(ts);
	}
	{
		// Render
		PROFILE_SCOPE("Renderer Background Prep");
		Bezel::RenderCommand::setClearColor({ 0.5546875, 0.5546875, 0.5546875, 1 });
		Bezel::RenderCommand::clear();
	}

	{
		PROFILE_SCOPE("Renderer Draw Call");
		// Camera
		Bezel::Renderer2D::beginScene(m_CameraController.getCamera());
		
		// Testing Quad and texture drawing

		// Normal Quad with rotation and flat color
		Bezel::Renderer2D::drawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		// Quad w/color connected to GUI and customizable
		Bezel::Renderer2D::drawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);
		// Using a texture and repeats it 10 times within scale constriction
		Bezel::Renderer2D::drawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CloudTexture, 10.f);
		
		Bezel::Renderer2D::endScene();
	}
	
}

void Sandbox2D::onImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	// Display profiling results in GUI layer
	for (auto& result : m_ProfileResults) {
		char label[50];
		strcpy(label, "%.3fms ");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();

	ImGui::End();
}

void Sandbox2D::onEvent(Bezel::Event& e) {
	m_CameraController.onEvent(e);
}