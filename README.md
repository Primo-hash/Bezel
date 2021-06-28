# Bezel
A graphics engine influenced by the Hazel engine tutorial from TheCherno.
Source: https://github.com/TheCherno/Hazel

Author: Abdulhadi Al-Sayed

## Description
The repository includes a sandbox application for testing with an example CMake setup
for cross platform adoption. The Bezel engine exists in the top vendor directory as a static (or shared with a few modifications),
and runs its own dependencies from another vendor directory.
The engine logic is made with STL headers and should be able to implement multiple libraries with the
same purpose but optimized for different platforms.

## Major changes
* Uses CMake (Tested on Windows/Unix)
* Cross platform compatible (Hazel can but doesn't)

## Requirements  
#### CMake  
#### ImGui
* 'docking' branch on github because the engine implements viewport and docking features (required)

# File structure

.  
+-- include/  
+-- out/  (Output directory on windows (might be called build/ on unix))  
+-- src/  
+-- vendor/  
| ‎‏‏‎ ‎‏‏‎ +-- bezel/	(The Engine library)  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- GUI/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- ImGui/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- ImGuiLayer.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- ImGuiLayer.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- include/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- events/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- AppEvent.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Event.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- KeyEvent.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- MouseEvent.h    
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- App.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Core.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Entrypoint.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Layer.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- LayerStack.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Log.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Window.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- platform/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- desktop/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- DesktopInput.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- DesktopInput.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- DesktopWindow.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- DesktopWindow.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- src/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- App.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Layer.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- LayerStack.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Log.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- vendor/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- glad/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- glew/  (To be removed)  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- glfw/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- glm/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- imgui/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- spdlog/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Bezel.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Precompiled.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Precompiled.h  
+-- application.cpp	(currently sandbox.cpp)  