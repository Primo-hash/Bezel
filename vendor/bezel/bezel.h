#pragma once
/*
*	Bezel.h filen er hovedsakelig ment for applikasjoner som tar i bruk Bezel engine
*/
#include "bezel/include/App.h"
#include "bezel/include/Layer.h"
#include "bezel/include/Log.h"

#include "bezel/core/Timestep.h"

// Input handling
#include "bezel/include/Input.h"
#include "bezel/include/InputCodes.h"

// GUI layer(s) template(s)
#include "bezel/GUI/ImGui/ImGuiLayer.h"

// Rendering
#include "bezel/include/renderer/Renderer.h"
#include "bezel/include/renderer/RenderCommand.h"

#include "bezel/include/renderer/Buffer.h"
#include "bezel/include/renderer/Shader.h"
#include "bezel/include/renderer/VertexArray.h"

#include "bezel/include/renderer/OrthographicCamera.h"

// Inngang for applikasjonsdefinisjon
#include "include/Entrypoint.h"

