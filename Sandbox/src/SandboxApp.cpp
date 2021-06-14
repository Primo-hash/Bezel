#include <spdlog/spdlog.h>
#include <Bezel.h>

class SandBox : public Bezel::App {
public:
	SandBox() {

	}

	~SandBox() {

	}
};

/*
	Returns a new application sandbox defined by Bezel.
*/
Bezel::App* Bezel::createApp() {
	return new SandBox;
}