cmake_minimum_required(VERSION 3.12)

# Desc/Def
set(BEZEL_VERSION "0.0.1")
project(Bezel VERSION ${BEZEL_VERSION} LANGUAGES CXX)

# Requirements
find_package(OpenGL REQUIRED)
include(GNUInstallDirs)

# Dependencies
add_subdirectory(vendor/glfw-3.3.2)
add_subdirectory(vendor/glew-cmake-2.1.0)
add_subdirectory(vendor/glm-0.9.9.8)
add_subdirectory(vendor/spdlog)

# Scope
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE 
../ 
/include
/src
/platform
)
target_precompile_headers(${PROJECT_NAME} INTERFACE "Precompiled.h")

# Library files
add_library(Engine SHARED
	# I am aware of the usage of GLOB to define directories
	# However it is strongly discouraged because the build system won't know
	# when to ask CMake to regenerate.
	# That is why I have chosen to list manually
	"include/Entrypoint.h" "include/Core.h" "include/App.h" "include/Log.h" "include/Window.h"
	"include/events/Event.h" "include/events/AppEvent.h" "include/events/KeyEvent.h" "include/events/MouseEvent.h"
	"src/App.cpp" "src/Log.cpp" 
	"platform/desktop/DesktopWindow.cpp" "platform/desktop/DesktopWindow.h"
	"Bezel.h"
	)

# Engine uses alias as Bezel here for linking
target_link_libraries(Engine PUBLIC 
	Bezel
	libglew_static
	glfw
	glm
	spdlog
	OpenGL::GL)

add_library(Bezel::Engine ALIAS Bezel)

# DLL exporting specific steps
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER 
	include/bezel.h
	)

# Compiler-specific flags to allow exporting symbols for Bezel
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    # G+
    target_compile_options(Engine PRIVATE -Wall -Wextra -fPIC -Wno-dev)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    # MSVC
    target_compile_options(Engine PRIVATE -Wno-dev /EHsc /MTd /W2 /c)
endif()

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})