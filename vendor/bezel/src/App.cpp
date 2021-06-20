#include "bezel/include/App.h"

#include "bezel/include/events/AppEvent.h"
#include "bezel/include/Log.h"

namespace Bezel {

	Bezel::App::App() {

	}

	Bezel::App::~App() {

	}

	void Bezel::App::run() {
		WindowResizeEvent e(1080, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			BZ_CLIENT_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))	// Window resizing not part of input, so should only be logged once
		{
			BZ_CLIENT_TRACE(e);
		}

		while (true);
	}

}