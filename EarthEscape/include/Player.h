#pragma once

#include "bezel/Bezel.h"

#include "Color.h"
#include "Random.h"

#include "ParticleSystem.h"

class Player {
private:
	glm::vec2 m_Position = { -10.0f, 0.0f };	// Starting position
	glm::vec2 m_Velocity = { 5.0f, 0.0f };		// Player speed

	float m_EnginePower = 0.5f;
	float m_Gravity = -0.4f;

	float m_Time = 0.0f;
	float m_SmokeEmitInterval = 0.4f;
	float m_SmokeNextEmitTime = m_SmokeEmitInterval;

	ParticleProps m_SmokeParticle, m_EngineParticle;
	ParticleSystem m_ParticleSystem;

	Bezel::Ref<Bezel::Texture2D> m_ShipTexture;
public:
	Player();

	void loadAssets();

	void onUpdate(Bezel::Timestep ts);
	void onRender();

	void onImGuiRender();

	void reset();

	float getRotation() { return m_Velocity.y * 4.0f - 90.0f; }
	const glm::vec2& getPosition() const { return m_Position; }

	uint32_t getScore() const { return (uint32_t)(m_Position.x + 10.0f) / 10.0f; }
};