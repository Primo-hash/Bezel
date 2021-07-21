cmake_minimum_required(VERSION 3.12)

# Desc/Def
set(BEZEL_VERSION "0.0.1")
project(Bezel VERSION ${BEZEL_VERSION} LANGUAGES CXX)

# Requirements
find_package(OpenGL REQUIRED)
include(GNUInstallDirs)

# Dependencies
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw-3.3.2)
add_subdirectory(vendor/glew-cmake-2.1.0)
add_subdirectory(vendor/glm-0.9.9.8)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/stb)

# Scope
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE 
	../
	)

target_precompile_headers(${PROJECT_NAME} INTERFACE "Precompiled.h")

# Library files
add_library(Engine STATIC
	# I am aware of the usage of GLOB to add files by regex
	# However it is strongly discouraged because the build system won't know
	# when to ask CMake to regenerate in some cases.
	# That is why I have chosen to list manually.

	# /GUI/ImGui
	"GUI/ImGui/ImGuiLayer.cpp" "GUI/ImGui/ImGuiLayer.h" "GUI/ImGui/ImGuiBuild.h"

	# /include
	"include/Entrypoint.h" "include/Core.h" "include/App.h" "include/Log.h" "include/Window.h"
	"include/Layer.h" "include/LayerStack.h" "include/InputCodes.h" "include/Input.h" "include/Timestep.h"

	# /include/events
	"include/events/Event.h" "include/events/AppEvent.h" "include/events/KeyEvent.h" "include/events/MouseEvent.h"

	# /include/renderer
	"include/renderer/Renderer.h" "include/renderer/RenderContext.h" "include/renderer/Shader.h" "include/renderer/Buffer.h"
	"include/renderer/VertexArray.h" "include/renderer/RenderCommand.h" "include/renderer/RenderAPI.h"
	"include/renderer/OrthographicCamera.h" "include/renderer/Texture.h" "include/renderer/CameraController.h"
	"include/renderer/Renderer2D.h" "include/renderer/GraphicsLibraryContext.h"

	# /src
	"src/App.cpp" "src/Log.cpp" "src/Layer.cpp" "src/LayerStack.cpp" "src/Shader.cpp" "src/Buffer.cpp" "src/Renderer.cpp"
	"src/VertexArray.cpp" "src/RenderAPI.cpp" "src/RenderCommand.cpp" "src/OrthographicCamera.cpp"  "src/Texture.cpp"
	"src/CameraController.cpp" "src/Renderer2D.cpp" "src/GraphicsLibraryContext.cpp"
	
	# /platform
	"platform/desktop/DesktopWindow.cpp" "platform/desktop/DesktopWindow.h" 
	"platform/desktop/DesktopInput.cpp" "platform/desktop/DesktopInput.h"

	# /platform/renderAPI/OpenGL
	"platform/renderAPI/OpenGL/OpenGLContext.cpp" "platform/renderAPI/OpenGL/OpenGLContext.h"
	"platform/renderAPI/OpenGL/OpenGLBuffer.cpp" "platform/renderAPI/OpenGL/OpenGLBuffer.h"
	"platform/renderAPI/OpenGL/OpenGLVertexArray.cpp" "platform/renderAPI/OpenGL/OpenGLVertexArray.h"
	"platform/renderAPI/OpenGL/OpenGLRenderAPI.cpp" "platform/renderAPI/OpenGL/OpenGLRenderAPI.h"
	"platform/renderAPI/OpenGL/OpenGLShader.cpp" "platform/renderAPI/OpenGL/OpenGLShader.h"
	"platform/renderAPI/OpenGL/OpenGLTexture.cpp" "platform/renderAPI/OpenGL/OpenGLTexture.h"
	"platform/renderAPI/OpenGL/OpenGLFuncVersion.h" "platform/renderAPI/OpenGL/OpenGLFuncVersion.cpp"

	# ./
	"Bezel.h"
	)

# Engine uses alias as Bezel here for linking
target_link_libraries(Engine PUBLIC 
	Bezel
	glad
	libglew_static
	glfw
	glm
	imgui
	spdlog
	stb
	OpenGL::GL)

add_library(Bezel::Engine ALIAS Bezel)
# Engine Options: 
#	- BZ_DEBUG              // Debugging mode
#   - BZ_DYNAMIC_LINK		// Required if this library is compiled as 'SHARED'
target_compile_definitions(Engine PUBLIC GLFW_INCLUDE_NONE BZ_DEBUG)


# Compiler/Platform specific flags to allow exporting symbols for Bezel
if (WIN32 OR CYGWIN)
    # WINDOWS AND CYGWIN COMPILER
	# BZ_DEBUG defined for Debug specific logging (more verbose), BZ_EXPORTS To export functions/classes from dll
	target_compile_definitions(Engine PRIVATE BZ_EXPORTS)
	target_compile_definitions(Engine PUBLIC BZ_PLATFORM_WINDOWS)
    target_compile_options(Engine PRIVATE /EHsc /MDd /c /MP)
endif (WIN32 OR CYGWIN)
if (UNIX)
    # UNIX (including MAC OS X)
	target_compile_definitions(Engine PRIVATE BZ_EXPORTS)
	target_compile_definitions(Engine PUBLIC BZ_PLATFORM_UNIX)
    target_compile_options(Engine PRIVATE -Wall -Wextra -fPIC)
endif (UNIX)

# DLL exporting specific steps
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER 
	include/bezel.h
	)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# C++ 17 required
set_property(TARGET Engine PROPERTY
	CXX_STANDARD 17
	)