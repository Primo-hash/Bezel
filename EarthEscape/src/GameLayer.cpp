#include "EarthEscape/include/layers/GameLayer.h"
#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Bezel;

/*
	Constructor for initializing camera and random number gen.
*/
GameLayer::GameLayer() : Layer("GameLayer") {
	auto& window = App::get().getWindow();
	createCamera(window.getWidth(), window.getHeight());

	Random::init();
}

/*
	First time setup of assets/functions before game loop
*/
void GameLayer::onAttach() {
	m_Level.init();		// Level setup

	// GUI text output
	ImGuiIO io = ImGui::GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("assets/OpenSans-Regular.ttf", 120.0f);
}

void GameLayer::onDetach() {

}

/*
	Game loop protocol
*/
void GameLayer::onUpdate(Bezel::Timestep ts) {
	m_Time += ts;													// Layer timer

	if ((int)(m_Time * 2.0f) % 2 != 0) {								// Text blink to catch attention
		m_Blink = !m_Blink;
	}

	if (m_Level.isGameOver()) {										// Check for game over from level
		m_State = GameState::GameOver;								// Set layer state to game over
	}

	const auto& playerPos = m_Level.getPlayer().getPosition();		// Get player position
	m_Camera->setPosition({ playerPos.x, playerPos.y, 0.0f });		// Attach main camera to player

	switch (m_State) {		// Game states
	case GameState::Play:
	{							// Game still in play
		m_Level.onUpdate(ts);	// Run game loop protocol for level
		break;
	}
	}

	// Render
	Bezel::RenderCommand::setClearColor({ 0.0f, 0.0f, 0.0f, 1 });	// Background color
	Bezel::RenderCommand::clear();									// Clear all draws for next frame

	Bezel::Renderer2D::beginScene(*m_Camera);						// Draw viewprojection
	m_Level.onRender();												// Draw camera
	Bezel::Renderer2D::endScene();									// Frame end protocol
}

/*
	Custom ImGui Layer for rendering game text based on game state
*/
void GameLayer::onImGuiRender() {
	switch (m_State) {
	case GameState::Play:				// In Play
	{
		// Render Score
		uint32_t playerScore = m_Level.getPlayer().getScore();
		std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
		ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, ImGui::GetWindowPos(), 0xffffffff, scoreStr.c_str());
		break;
	}
	case GameState::MainMenu:			// In main menu
	{
		// Text position on screen
		auto pos = ImGui::GetWindowPos();
		auto width = App::get().getWindow().getWidth();
		auto height = App::get().getWindow().getHeight();
		pos.x += width * 0.5f - 300.0f;
		pos.y += 50.0f;

		// Render blinking "Click to play" text
		if (m_Blink)
			ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");
		break;
	}
	case GameState::GameOver:			// On game over
	{
		// Text position on screen
		auto pos = ImGui::GetWindowPos();
		auto width = App::get().getWindow().getWidth();
		auto height = App::get().getWindow().getHeight();
		pos.x += width * 0.5f - 300.0f;
		pos.y += 50.0f;

		// Render blinking "Click to play" text
		if (m_Blink) {
			ImGui::GetForegroundDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");
		}

		// Final score below click to play message
		pos.x += 200.0f;
		pos.y += 150.0f;

		// Render score
		uint32_t playerScore = m_Level.getPlayer().getScore();
		std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
		ImGui::GetForegroundDrawList()->AddText(m_Font, 48.0f, pos, 0xffffffff, scoreStr.c_str());
		break;
	}
	}
}

/*
	GameLayer events respond to window resizing and mouse clicks
*/
void GameLayer::onEvent(Bezel::Event& e) {
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowResizeEvent>(BZ_BIND_EVENT_FN(GameLayer::onWindowResize));
	dispatcher.Dispatch<MouseButtonPressedEvent>(BZ_BIND_EVENT_FN(GameLayer::onMouseButtonPressed));
}

/*
	Mouse button event
*/
bool GameLayer::onMouseButtonPressed(Bezel::MouseButtonPressedEvent& e) {
	if (m_State == GameState::GameOver) {
		m_Level.reset();		// Restart level
	}

	m_State = GameState::Play;	// Set game state to play
	return false;
}

/*
	Window Resize event
*/
bool GameLayer::onWindowResize(Bezel::WindowResizeEvent& e) {
	createCamera(e.getWidth(), e.getHeight());		// Readjusts camera to fit new window size
	return false;
}

/*
	For camera adjustment/ setup to window size
*/
void GameLayer::createCamera(uint32_t width, uint32_t height) {
	float aspectRatio = (float)width / (float)height;
	float zoom = 10.0f;
	float bottom = -zoom;
	float top = zoom;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;

	m_Camera = createScope<OrthographicCamera>(left, right, bottom, top);
}