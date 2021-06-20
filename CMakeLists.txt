cmake_minimum_required(VERSION 3.12)

project(Sandbox)

find_package(OpenGL REQUIRED)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)	# For exporting in windows
set(CMAKE_POSITION_INDEPENDENT_CODE ON)		# For static libraries (spdlog) included by shared libraries

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