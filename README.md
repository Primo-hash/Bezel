# Bezel
A game engine influenced by the Hazel engine tutorial from TheCherno.
Source: https://github.com/TheCherno/Hazel


# File structure

.  
+-- application.cpp	(currently sandbox.cpp)  
+-- vendor/  
| ‎‏‏‎ ‎‏‏‎ +-- bezel/	(The Engine library)  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- include/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- events/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- AppEvent.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Event.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- KeyEvent.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- MouseEvent.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- App.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Core.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Entrypoint.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Log.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- platform/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- desktop/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- DesktopWindow.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- DesktopWindow.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- src/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- App.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Log.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- vendor/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- glew/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- glfw/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- glm/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- spdlog/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Bezel.h  
+-- src/  
+-- include/  
