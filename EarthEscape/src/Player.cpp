#include "EarthEscape/include/Player.h"

#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace Bezel;

Player::Player() {
	// Smoke
	m_SmokeParticle.position = { 0.0f, 0.0f };
	m_SmokeParticle.velocity = { -2.0f, 0.0f }, m_SmokeParticle.velocityVariation = { 4.0f, 2.0f };
	m_SmokeParticle.sizeBegin = 0.35f, m_SmokeParticle.sizeEnd = 0.0f, m_SmokeParticle.sizeVariation = 0.15f;
	m_SmokeParticle.colorBegin = { 0.8f, 0.8f, 0.8f, 1.0f };
	m_SmokeParticle.colorEnd = { 0.6f, 0.6f, 0.6f, 1.0f };
	m_SmokeParticle.lifetime = 4.0f;

	// Flames
	m_EngineParticle.position = { 0.0f, 0.0f };
	m_EngineParticle.velocity = { -2.0f, 0.0f }, m_EngineParticle.velocityVariation = { 3.0f, 1.0f };
	m_EngineParticle.sizeBegin = 0.5f, m_EngineParticle.sizeEnd = 0.0f, m_EngineParticle.sizeVariation = 0.3f;
	m_EngineParticle.colorBegin = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_EngineParticle.colorEnd = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f , 1.0f };
	m_EngineParticle.lifetime = 1.0f;
}

void Player::loadAssets() {
	m_ShipTexture = Texture2D::create("assets/textures/RocketShip.png");
}

void Player::onUpdate(Bezel::Timestep ts) {
	m_Time += ts;

	if (Input::isKeyPressed(BZ_KEY_SPACE)) {
		m_Velocity.y += m_EnginePower;
		if (m_Velocity.y < 0.0f) {
			m_Velocity.y += m_EnginePower * 2.0f;
		}

		// Flames
		glm::vec2 emissionPoint = { 0.0f, -0.6f };
		float rotation = glm::radians(getRotation());
		glm::vec4 rotated = glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::vec4(emissionPoint, 0.0f, 1.0f);
		m_EngineParticle.position = m_Position + glm::vec2{ rotated.x, rotated.y };
		m_EngineParticle.velocity.y = -m_Velocity.y * 0.2f - 0.2f;
		m_ParticleSystem.emit(m_EngineParticle);
	} 
	else {
		m_Velocity.y += m_Gravity;
	}

	m_Velocity.y = glm::clamp(m_Velocity.y, -20.0f, 20.0f);
	m_Position += m_Velocity * (float)ts;

	// Particles
	if (m_Time > m_SmokeNextEmitTime)
	{
		m_SmokeParticle.position = m_Position;
		m_ParticleSystem.emit(m_SmokeParticle);
		m_SmokeNextEmitTime += m_SmokeEmitInterval;
	}

	m_ParticleSystem.onUpdate(ts);
}

void Player::onRender() {
	m_ParticleSystem.onRender();
	Renderer2D::drawRotatedQuad({ m_Position.x, m_Position.y, 0.5f }, { 1.0f, 1.3f }, glm::radians(getRotation()), m_ShipTexture);
}

void Player::onImGuiRender() {
	ImGui::DragFloat("Engine Power", &m_EnginePower, 0.1f);
	ImGui::DragFloat("Gravity", &m_Gravity, 0.1f);
}

void Player::reset()
{
	m_Position = { -10.0f, 0.0f };
	m_Velocity = { 5.0f, 0.0f };
}