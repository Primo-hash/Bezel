#include "bezel/Bezel.h"
#include <spdlog/spdlog.h>


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
		if (event.GetEventType() == Bezel::EventType::KeyPressed) {
			Bezel::KeyPressedEvent& e = (Bezel::KeyPressedEvent&)event;
			if (e.GetKeyCode() == BZ_KEY_TAB) {
				BZ_CLIENT_TRACE("Tab key is pressed (event)!");
			}
			BZ_CLIENT_TRACE("{0}", (char)e.GetKeyCode());
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
		pushOverlay(new Bezel::ImGuiLayer());
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
