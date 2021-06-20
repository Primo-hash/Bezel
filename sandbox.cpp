#include "bezel/Bezel.h"
#include <spdlog/spdlog.h>


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
	return new SandBox();
}
