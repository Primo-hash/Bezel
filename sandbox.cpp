/*
	This is currently a testing ground for Bezel Engine features
*/
#include "bezel/Bezel.h"

#include "imgui.h"


/*
	An example Layer class that draws a GUI
*/
class ExampleLayer : public Bezel::Layer {
public:
	ExampleLayer() : Layer("Layer") {}

	void onUpdate() override {
		
		// Logs if TAB key is currently pressed
		if (Bezel::Input::isKeyPressed(BZ_KEY_TAB))
			BZ_CLIENT_TRACE("Tab key is pressed (poll)!");
	}

	virtual void onImGuiRender() override
	{
		// Makes a simple window in the GUI to test
		ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_FirstUseEver);	// Sets an initial window size for first time this window is rendered.
		ImGui::Begin("Yo");
		ImGui::Text("yo");
		ImGui::End();
	}

	void onEvent(Bezel::Event& event) override {
		// Logs keystrokes and when TAB key is pressed using Event system
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
		pushLayer(new ExampleLayer());	// Pushes example overlay with a GUI
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
