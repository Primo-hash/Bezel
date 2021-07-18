#pragma once

#include "bezel/Bezel.h"

class Sandbox2D : public Bezel::Layer {
private:
	Bezel::OrthographicCameraController m_CameraController;

	// VA testing
	Bezel::Ref<Bezel::VertexArray> m_SquareVA;
	Bezel::Ref<Bezel::Shader> m_FlatColorShader;

	// Textures testing
	Bezel::Ref<Bezel::Texture2D> m_CloudTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void onAttach() override;
	virtual void onDetach() override;

	void onUpdate(Bezel::Timestep ts) override;
	virtual void onImGuiRender() override;
	void onEvent(Bezel::Event& e) override;
};