/*
	This is currently a testing ground for Bezel Engine features
	using an example layer.
	Other example layers in header and source folders are also included.
*/
#include "bezel/Bezel.h"
#include "bezel/include/Entrypoint.h"
#include "bezel/platform/renderAPI/OpenGL/OpenGLShader.h"
#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "include/layers/Sandbox2D.h"	// Example layer making use of 2D renderer
#include "include/layers/ExampleLayer.h"

/*
	An example Overlay class
*/
class ExampleOverlay : public Bezel::Layer {
public:
	ExampleOverlay() : Layer("Overlay") {}

	void onUpdate(Bezel::Timestep ts) override {
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
	SandBox(Bezel::WindowSpecs specs) : App(specs) {
		// SETUP
		setAppIcon("assets/textures/cloudberry.png");

		// LAYERS
		//pushLayer(new ExampleLayer());	// Pushes example overlay with a GUI
		pushLayer(new Sandbox2D());			// Pushes example layer for 2D rendering
	}

	~SandBox() {

	}
};

/*
	Returns a new application sandbox defined by Bezel.
	The createApp function has to be defined by the application.
*/
Bezel::App* Bezel::createApp() {
	auto windowSpecs = Bezel::WindowSpecs("Sandbox", 1080, 720);

	return new SandBox(windowSpecs);
}
