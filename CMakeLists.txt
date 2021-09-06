cmake_minimum_required(VERSION 3.12)

# Desc/Def
set(SANDBOX_VERSION "0.0.1")
project(
  Sandbox
  VERSION ${SANDBOX_VERSION}
  LANGUAGES CXX)

find_package(OpenGL REQUIRED)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON) # For exporting in windows
set(CMAKE_POSITION_INDEPENDENT_CODE ON)  # For static libraries (spdlog) included
                                         # by shared libraries

# Build location options
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Debugging mode
set(DEBUG true)

# Dependencies
add_subdirectory(vendor/bezel)

# SANDBOX APP EXECUTABLE

# Debug on (Currently only windows)
if(NOT ${DEBUG})
    if (WIN32 OR CYGWIN)
        # Removes debug/log console
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

        add_executable(${PROJECT_NAME} WIN32 Sandbox/sandbox.cpp 
        # .Sandbox/src
        "Sandbox/src/Sandbox2D.cpp" "Sandbox/src/ExampleLayer.cpp"

        "EarthEscape/src/Random.cpp" "EarthEscape/include/Random.h"

        # .Sandbox/include/layers
        "Sandbox/include/layers/Sandbox2D.h" "Sandbox/include/layers/ExampleLayer.h"
        )
    endif (WIN32 OR CYGWIN)
endif(NOT ${DEBUG})

# Debug off
if (${DEBUG})
    # UNIX (including MAC OS X)
	add_executable(${PROJECT_NAME} Sandbox/sandbox.cpp 
        # .Sandbox/src
        "Sandbox/src/Sandbox2D.cpp" "Sandbox/src/ExampleLayer.cpp"

        "EarthEscape/src/Random.cpp" "EarthEscape/include/Random.h"

        # .Sandbox/include/layers
        "Sandbox/include/layers/Sandbox2D.h" "Sandbox/include/layers/ExampleLayer.h"
  "EarthEscape/include/ParticleSystem.h" "EarthEscape/src/ParticleSystem.cpp" "EarthEscape/include/Player.h" "EarthEscape/src/Player.cpp" "EarthEscape/include/Level.h" "EarthEscape/src/Level.cpp")
endif (${DEBUG})

# Engine is the Bezel engine .lib file The rest of linked libraries are there
# for convenience since the engine utilizes them.
target_link_libraries(
  ${PROJECT_NAME}
  Engine
  glad
  glfw
  glm
  imgui
  spdlog
  stb
  OpenGL::GL
  )

# EARTHESCAPE APP EXECUTABLE

# Note this app is still part of the Sandbox cmake project
# meaning all executables by this project have to be compiled at the same time

# Debug on (Currently only windows)
if(NOT ${DEBUG})
    if (WIN32 OR CYGWIN)
        # Removes debug/log console
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

        add_executable(EarthEscape WIN32 EarthEscape/earthescape.cpp 
        # .EarthEscape/src
        "EarthEscape/src/GameLayer.cpp" "EarthEscape/src/Random.cpp"
        "EarthEscape/src/ParticleSystem.cpp" "EarthEscape/src/Player.cpp"
        "EarthEscape/src/Level.cpp"

        # .EarthEscape/include
        "EarthEscape/include/Color.h" "EarthEscape/include/Random.h"
        "EarthEscape/include/ParticleSystem.h" "EarthEscape/include/Player.h"
        "EarthEscape/include/Level.h"

        # .EarthEscape/include/layers
        "EarthEscape/include/layers/GameLayer.h"
        )
    endif (WIN32 OR CYGWIN)
endif(NOT ${DEBUG})

# Debug off
if (${DEBUG})
    # UNIX (including MAC OS X)
	add_executable(EarthEscape EarthEscape/earthescape.cpp 
        # .EarthEscape/src
        "EarthEscape/src/GameLayer.cpp" "EarthEscape/src/Random.cpp"
        "EarthEscape/src/ParticleSystem.cpp" "EarthEscape/src/Player.cpp"
        "EarthEscape/src/Level.cpp"

        # .EarthEscape/include
        "EarthEscape/include/Color.h" "EarthEscape/include/Random.h"
        "EarthEscape/include/ParticleSystem.h" "EarthEscape/include/Player.h"
        "EarthEscape/include/Level.h"

        # .EarthEscape/include/layers
        "EarthEscape/include/layers/GameLayer.h"
        )
endif (${DEBUG})

target_link_libraries(
  EarthEscape
  Engine
  glad
  glfw
  glm
  imgui
  spdlog
  stb
  OpenGL::GL
  )

# OPTIONS

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

include_directories(${PROJECT_NAME} INTERFACE 
	${CMAKE_CURRENT_LIST_DIR}
)

target_compile_definitions(${PROJECT_NAME} PUBLIC GLEW_STATIC)

if (WIN32 OR CYGWIN)
    # WINDOWS AND CYGWIN COMPILER
    target_compile_options(${PROJECT_NAME} PRIVATE /MP)
endif (WIN32 OR CYGWIN)

  add_custom_command(
  # Assets to be copied to build folder
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_LIST_DIR}/assets
  ${CMAKE_CURRENT_BINARY_DIR}/bin/assets
  
  # GUI config to be copied to build folder
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  ${CMAKE_CURRENT_LIST_DIR}/imgui.ini
  ${CMAKE_CURRENT_BINARY_DIR}/bin
  )