#pragma once

#include "Player.h"

/*
	Main level obstacles
*/
struct Pillar {
	glm::vec3 topPosition = { 0.0f, 10.0f, 0.0f };
	glm::vec2 topScale = { 15.0f, 20.0f };

	glm::vec3 bottomPosition = { 10.0f, 10.0f, 0.0f };
	glm::vec2 bottomScale = { 15.0f, 20.0f };
};

class Level {
private:
	Player m_Player;

	bool m_GameOver = false;

	float m_PillarTarget = 30.0f;
	int m_PillarIndex = 0;
	glm::vec3 m_PillarHSV = { 0.0f, 0.8f, 0.8f };	// Hue Saturation Value (Color)

	std::vector<Pillar> m_Pillars;

	Bezel::Ref<Bezel::Texture2D> m_TriangleTexture;

	void createPillar(int index, float offset);
	bool collisionTest();

	void gameOver();
public:
	void init();

	void onUpdate(Bezel::Timestep ts);
	void onRender();

	void onImGuiRender();

	bool isGameOver() const { return m_GameOver; }
	void reset();

	Player& getPlayer() { return m_Player; }
};