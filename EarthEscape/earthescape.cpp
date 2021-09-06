#include "bezel/Bezel.h"
#include "bezel/include/Entrypoint.h"

#include "include/layers/GameLayer.h"

class EarthEscape : public Bezel::App {
public:
	EarthEscape(Bezel::WindowSpecs specs) : App(specs) {
		// SETUP
		setAppIcon("assets/textures/RocketShip.png");

		pushLayer(new GameLayer());
	}

	~EarthEscape() {

	}
};

Bezel::App* Bezel::createApp() {
	auto windowSpecs = Bezel::WindowSpecs("Earth Escape", 1080, 720);

	return new EarthEscape(windowSpecs);
}