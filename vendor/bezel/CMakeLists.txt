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
target_include_directories(${PROJECT_NAME} INTERFACE ../)

# Library files
add_library(Engine SHARED
	"include/Entrypoint.h"
	"include/Core.h"
	"Bezel.h"
	"src/App.cpp" 
	"src/Log.cpp" 
	"include/Log.h" 
	"include/App.h")

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
    # G++
    target_compile_options(Bezel::Engine PRIVATE -Wall -Wextra)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    # MSVC
    target_compile_options(Bezel::Engine PRIVATE /EHsc /MTd /W2 /c)
endif()

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})