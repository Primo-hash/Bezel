#pragma once

#include "bezel/Bezel.h"

/*
	An example Layer class that currently draws a GUI and a demonstration of renderer functionality
*/
class ExampleLayer : public Bezel::Layer {
private:
	// SHADER
	Bezel::ShaderLibrary m_ShaderLibrary;
	Bezel::Ref<Bezel::Shader> m_Shader;
	Bezel::Ref<Bezel::VertexArray> m_VertexArray;

	Bezel::Ref<Bezel::Shader> m_FlatColorShader;
	Bezel::Ref<Bezel::VertexArray> m_SquareVA;

	Bezel::Ref<Bezel::Texture2D> m_Texture, m_CloudBerryTexture;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

	// PROJECTION
	Bezel::OrthographicCameraController m_CameraController;
public:
	ExampleLayer();
	virtual ~ExampleLayer();

	void onUpdate(Bezel::Timestep ts) override;
	virtual void onImGuiRender() override;
	void onEvent(Bezel::Event& e) override;

};