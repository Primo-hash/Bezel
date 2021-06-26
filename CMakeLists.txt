cmake_minimum_required(VERSION 3.12)

# Desc/Def
set(SANDBOX_VERSION "0.0.1")
project(Sandbox VERSION ${SANDBOX_VERSION} LANGUAGES CXX)


find_package(OpenGL REQUIRED)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)	# For exporting in windows
set(CMAKE_POSITION_INDEPENDENT_CODE ON)		# For static libraries (spdlog) included by shared libraries

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${PROJECT_NAME}
	sandbox.cpp
	)
set_property(TARGET ${PROJECT_NAME} PROPERTY
	CXX_STANDARD 17
	)


# Engine Options:
#	- BZ_DEBUG		// Debugging mode 
target_compile_definitions(${PROJECT_NAME} PUBLIC GLEW_STATIC)

# Dependencies
add_subdirectory(vendor/bezel)

# Engine is the Bezel engine .lib file
# The rest of linked libraries are there for convenience
# since the engine utilizes them.
target_link_libraries(${PROJECT_NAME}
	Engine
	glad
	libglew_static
	glfw
	glm
	imgui
	spdlog
	OpenGL::GL
	)