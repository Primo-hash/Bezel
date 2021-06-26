#pragma once
#include "bezel/Precompiled.h"

#define IMGUI_API __declspec(dllexport)
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "imgui_impl_opengl3.cpp"
#include "imgui_impl_glfw.cpp"