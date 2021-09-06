#pragma once

#include "bezel/Bezel.h"

#include "EarthEscape/include/Level.h"
#include "imgui.h"

class GameLayer : public Bezel::Layer {
private:
	Bezel::Scope<Bezel::OrthographicCamera> m_Camera;
	Level m_Level;
	ImFont* m_Font;
	float m_Time = 0.0f;
	bool m_Blink = false;

	enum class GameState {
		Play = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_State = GameState::MainMenu;

	void createCamera(uint32_t width, uint32_t height);
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void onAttach() override;
	virtual void onDetach() override;

	void onUpdate(Bezel::Timestep ts) override;
	virtual void onImGuiRender() override;
	void onEvent(Bezel::Event& e) override;
	bool onMouseButtonPressed(Bezel::MouseButtonPressedEvent& e);
	bool onWindowResize(Bezel::WindowResizeEvent& e);
};