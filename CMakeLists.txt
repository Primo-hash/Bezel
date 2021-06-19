cmake_minimum_required(VERSION 3.12)

project(Sandbox)

find_package(OpenGL REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(vendor/bezel)

add_executable(${PROJECT_NAME}
	sandbox.cpp
	)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLEW_STATIC)

# Engine is the Bezel engine .lib file
target_link_libraries(${PROJECT_NAME}
	Engine
	libglew_static
	glfw
	glm
	spdlog
	OpenGL::GL
	)

IF($(CMAKE_SYSTEM_NAME) STREQUAL Windows)
	#add_compile_definitions(
	#BZ_PLATFORM_WINDOWS
	#BZ_DEBUG
	#)
	set(ENV{BZ_PLATFORM_WINDOWS} 1)
	set(ENV{BZ_BUILD_DLL} 1)
ELSE($(CMAKE_SYSTEM_NAME) STREQUAL Linux)
	#add_compile_definitions(
	#BZ_PLATFORM_LINUX
	#BZ_DEBUG
	#)
	set(ENV{BZ_PLATFORM_LINUX} 1)
	set(ENV{BZ_BUILD_DLL} 1)
ENDIF()