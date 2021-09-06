#pragma once

#include "bezel/Bezel.h"

struct ParticleProps
{
	glm::vec2 position;
	glm::vec2 velocity, velocityVariation;
	glm::vec4 colorBegin, colorEnd;
	float sizeBegin, sizeEnd, sizeVariation;
	float lifetime = 1.0f;
};

class ParticleSystem {
private:
	struct Particle
	{
		glm::vec2 position;
		glm::vec2 velocity;
		glm::vec4 colorBegin, colorEnd;
		float rotation = 0.0f;
		float sizeBegin, sizeEnd;

		float lifetime = 1.0f;
		float lifeRemaining = 0.0f;

		bool active = false;
	};

	std::vector<Particle> m_ParticlePool;
	uint32_t m_PoolIndex = 999;
public:
	ParticleSystem();

	void emit(const ParticleProps& particleProps);

	void onUpdate(Bezel::Timestep ts);
	void onRender();
};