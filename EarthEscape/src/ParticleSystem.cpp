#include "EarthEscape/include/ParticleSystem.h"

#include "EarthEscape/include/Random.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

ParticleSystem::ParticleSystem()
{
	m_ParticlePool.resize(1000);
}

void ParticleSystem::emit(const ParticleProps& particleProps)
{
	Particle& particle = m_ParticlePool[m_PoolIndex];
	particle.active = true;
	particle.position = particleProps.position;
	particle.rotation = Random::randFloat() * 2.0f * glm::pi<float>();

	// Velocity
	particle.velocity = particleProps.velocity;
	particle.velocity.x += particleProps.velocityVariation.x * (Random::randFloat() - 0.5f);
	particle.velocity.y += particleProps.velocityVariation.y * (Random::randFloat() - 0.5f);

	// Color
	particle.colorBegin = particleProps.colorBegin;
	particle.colorEnd = particleProps.colorEnd;

	// Size
	particle.sizeBegin = particleProps.sizeBegin + particleProps.sizeVariation * (Random::randFloat() - 0.5f);
	particle.sizeEnd = particleProps.sizeEnd;

	// Life
	particle.lifetime = particleProps.lifetime;
	particle.lifeRemaining = particleProps.lifetime;

	m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}

void ParticleSystem::onUpdate(Bezel::Timestep ts)
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.active) {
			continue;
		}

		if (particle.lifeRemaining <= 0.0f) {
			particle.active = false;
			continue;
		}

		particle.lifeRemaining -= ts;
		particle.position += particle.velocity * (float)ts;
		particle.rotation += 0.01f * ts;
	}
}

void ParticleSystem::onRender()
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.active) {
			continue;
		}

		float life = particle.lifeRemaining / particle.lifetime;
		glm::vec4 color = glm::lerp(particle.colorEnd, particle.colorBegin, life);
		color.a = color.a * life;

		float size = glm::lerp(particle.sizeEnd, particle.sizeBegin, life);
		Bezel::Renderer2D::drawRotatedQuad(particle.position, { size, size }, particle.rotation, color);
	}
}