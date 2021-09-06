#include "EarthEscape/include/Level.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace Bezel;

/*
	Helper function for converting HSV color to RGB
*/
static glm::vec4 HSVtoRGB(const glm::vec3& hsv) {
	int H = (int)(hsv.x * 360.0f);
	double S = hsv.y;
	double V = hsv.z;

	double C = S * V;
	double X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
	double m = V - C;
	double Rs, Gs, Bs;

	if (H >= 0 && H < 60) {
		Rs = C;
		Gs = X;
		Bs = 0;
	}
	else if (H >= 60 && H < 120) {
		Rs = X;
		Gs = C;
		Bs = 0;
	}
	else if (H >= 120 && H < 180) {
		Rs = 0;
		Gs = C;
		Bs = X;
	}
	else if (H >= 180 && H < 240) {
		Rs = 0;
		Gs = X;
		Bs = C;
	}
	else if (H >= 240 && H < 300) {
		Rs = X;
		Gs = 0;
		Bs = C;
	}
	else {
		Rs = C;
		Gs = 0;
		Bs = X;
	}

	return { (Rs + m), (Gs + m), (Bs + m), 1.0f };
}


static bool pointInTri(const glm::vec2& p, glm::vec2& p0, const glm::vec2& p1, const glm::vec2& p2) {
	float s = p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y;
	float t = p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x + (p1.x - p0.x) * p.y;
	
	if ((s < 0) != (t < 0)) {
		return false;
	}

	float A = -p1.y * p2.x + p0.y * (p2.x - p1.x) + p0.x * (p1.y - p2.y) + p1.x * p2.y;

	return A < 0 ? (s <= 0 && s + t >= A) : (s >= 0 && s + t <= A);
}


void Level::init() {
	m_TriangleTexture = Texture2D::create("assets/textures/Triangle.png");
	m_Player.loadAssets();

	m_Pillars.resize(5);
	for (int i = 0; i < 5; i++)
		createPillar(i, i * 10.0f);
}

void Level::onUpdate(Bezel::Timestep ts) {
	m_Player.onUpdate(ts);

	if (collisionTest()) {
		gameOver();
		return;
	}

	// Interpolation of pillar color
	m_PillarHSV.x += 0.1f * ts;
	if (m_PillarHSV.x > 1.0f) {
		m_PillarHSV.x = 0.0f;
	}

	// Continuous generation of pillars after crossing first 3 pillars
	// Pillar index is cycled from 0 to 4
	// Meaning on the 4th pillar generated the 5th one will take
	// The place of the 1st pillar in memory.
	if (m_Player.getPosition().x > m_PillarTarget) {
		createPillar(m_PillarIndex, m_PillarTarget + 20.0f);
		BZ_CLIENT_INFO(m_PillarIndex);
		m_PillarIndex = ++m_PillarIndex % m_Pillars.size();
		BZ_CLIENT_INFO(m_PillarIndex);
		m_PillarTarget += 10.0f;
	}
}

void Level::onRender() {
	const auto& playerPos = m_Player.getPosition();

	glm::vec4 color = HSVtoRGB(m_PillarHSV);

	// Background
	Renderer2D::drawQuad({ playerPos.x, 0.0f, -0.8f }, { 50.0f, 50.0f }, { 0.3f, 0.3f, 0.3f, 1.0f });

	// Floor and ceiling
	Renderer2D::drawQuad({ playerPos.x,  34.0f }, { 50.0f, 50.0f }, color);
	Renderer2D::drawQuad({ playerPos.x, -34.0f }, { 50.0f, 50.0f }, color);

	for (auto& pillar : m_Pillars) {
		Renderer2D::drawRotatedQuad(pillar.topPosition, pillar.topScale, glm::radians(180.0f), m_TriangleTexture, 1.0f, color);
		Renderer2D::drawRotatedQuad(pillar.bottomPosition, pillar.bottomScale, 0.0f, m_TriangleTexture, 1.0f, color);
	}

	m_Player.onRender();
}

void Level::onImGuiRender() {
	m_Player.onImGuiRender();
}

void Level::createPillar(int index, float offset) {

	Pillar& pillar = m_Pillars[index];		// Pillar placement in memory
	pillar.topPosition.x = offset;			// Position based on
	pillar.bottomPosition.x = offset;		// offset

	// For blending triangle textures together
	// Removing will show textures colliding and the renderer not
	// Knowing what to render on top of what
	pillar.topPosition.z = index * 0.1f - 0.5f;
	pillar.bottomPosition.z = index * 0.1f - 0.5f + 0.05f;

	// Randomized center between top/bottom pillars
	float center = Random::randFloat() * 35.0f - 17.5f;
	float gap = 2.0f + Random::randFloat() * 5.0f;

	pillar.topPosition.y = 10.0f - ((10.0f - center) * 0.2f) + gap * 0.5f;
	pillar.bottomPosition.y = -10.0f - ((-10.0f - center) * 0.2f) - gap * 0.5f;
}

bool Level::collisionTest() {
	// Check if player has hit top/bottom walls
	if (glm::abs(m_Player.getPosition().y) > 8.5f) {
		return true;
	}

	// Player's hitbox consists of 4 corners
	glm::vec4 playerVertices[5] = {
		{ -0.3f, -0.5f, 0.0f, 1.0f },
		{  0.3f, -0.5f, 0.0f, 1.0f },
		{  0.3f,  0.25f, 0.0f, 1.0f },
		{ -0.3f,  0.25f, 0.0f, 1.0f },
		{  0.0f,  0.5f, 0.0f, 1.0f }
	};

	// Update hitbox based on player's position
	const auto& pos = m_Player.getPosition();
	glm::vec4 playerTransformedVerts[5];
	for (int i = 0; i < 5; i++) {
		playerTransformedVerts[i] = glm::translate(glm::mat4(1.0f), { pos.x, pos.y, 0.0f })
			* glm::rotate(glm::mat4(1.0f), glm::radians(m_Player.getRotation()), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { 1.0f, 1.3f, 1.0f })
			* playerVertices[i];
	}

	// To match Triangle.png (each hitbox corner is 10% from the texture edge)
	// Because the image sides are further away from the triangle
	glm::vec4 pillarVertices[3] = {
		{ -0.5f + 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
		{  0.5f - 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
		{  0.0f + 0.0f,  0.5f - 0.1f, 0.0f, 1.0f },
	};

	// For each bottom/top set of pillars
	for (auto& p : m_Pillars) {
		glm::vec2 tri[3];

		// Update hitbox for each top pillar based on position
		for (int i = 0; i < 3; i++) {
			tri[i] = glm::translate(glm::mat4(1.0f), { p.topPosition.x, p.topPosition.y, 0.0f })
				* glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), { p.topScale.x, p.topScale.y, 1.0f })
				* pillarVertices[i];
		}

		// Test for collision by matching every vertex of player and top pillar hitboxes
		for (auto& vert : playerTransformedVerts) {
			if (pointInTri({ vert.x, vert.y }, tri[0], tri[1], tri[2])) {
				return true;	// Collision
			}
		}

		// Update hitbox bottom pillar based on position
		for (int i = 0; i < 3; i++) {
			tri[i] = glm::translate(glm::mat4(1.0f), { p.bottomPosition.x, p.bottomPosition.y, 0.0f })
				* glm::scale(glm::mat4(1.0f), { p.bottomScale.x, p.bottomScale.y, 1.0f })
				* pillarVertices[i];
		}

		// Test for collision by matching every vertex of player and bottom pillar hitboxes
		for (auto& vert : playerTransformedVerts) {
			if (pointInTri({ vert.x, vert.y }, tri[0], tri[1], tri[2]))
				return true;	// Collision
		}

	}

	return false;	// No Collision
}

/*
	Sets level state to be game over
*/
void Level::gameOver() {
	m_GameOver = true;
}

/*
	Resets all necessary values for restarting the level
*/
void Level::reset() {
	m_GameOver = false;

	m_Player.reset();

	m_PillarTarget = 30.0f;
	m_PillarIndex = 0;
	for (int i = 0; i < 5; i++) {
		createPillar(i, i * 10.0f);
	}
}