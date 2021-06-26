#include "bezel/Bezel.h"
#include <spdlog/spdlog.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}

/*
	An example Layer class
*/
class ExampleLayer : public Bezel::Layer {
public:
	ExampleLayer() : Layer("Layer") {}

	void onUpdate() override {
		if (Bezel::Input::isKeyPressed(BZ_KEY_TAB))
			BZ_CLIENT_TRACE("Tab key is pressed (poll)!");
	}

	void onEvent(Bezel::Event& event) override {
		if (event.getEventType() == Bezel::EventType::KeyPressed) {
			Bezel::KeyPressedEvent& e = (Bezel::KeyPressedEvent&)event;
			if (e.getKeyCode() == BZ_KEY_TAB) {
				BZ_CLIENT_TRACE("Tab key is pressed (event)!");
			}
			BZ_CLIENT_TRACE("{0}", (char)e.getKeyCode());
		}
	}

};

/*
	An example Overlay class
*/
class ExampleOverlay : public Bezel::Layer {
public:
	ExampleOverlay() : Layer("Overlay") {}

	void onUpdate() override {
		BZ_CLIENT_INFO("Overlay::Update");
	}

	void onEvent(Bezel::Event& event) override {
		BZ_CLIENT_TRACE("{0}", event);
	}

};

/*
	An example application class
*/
class SandBox : public Bezel::App {
public:
	SandBox() {
		pushLayer(new ExampleLayer());
	}

	~SandBox() {

	}
};

/*
	Returns a new application sandbox defined by Bezel.
*/
Bezel::App* Bezel::createApp() {
	return new SandBox();
}
