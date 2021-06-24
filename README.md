# Bezel
A game engine influenced by the Hazel engine tutorial from TheCherno.
Source: https://github.com/TheCherno/Hazel

Author: Abdulhadi Al-Sayed

## Description
The repository includes a sandbox application for testing with an example CMake setup
for cross platform adoption. The Bezel engine exists in the top vendor directory as a dll,
and runs its own dependencies from another vendor directory.
The engine logic is made with STL headers and should be able to implement multiple libraries with the
same purpose but optimized for different platforms.

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
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- DesktopWindow.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- DesktopWindow.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- src/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- App.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Layer.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- LayerStack.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Log.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- vendor/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- glew/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- glfw/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- glm/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- spdlog/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Bezel.h  
+-- application.cpp	(currently sandbox.cpp)  