#include "bezel/Precompiled.h"
#include "bezel/include/renderer/RenderCommand.h"

namespace Bezel {

	Scope<RenderAPI> RenderCommand::s_RenderAPI = RenderAPI::create();

}