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
* Cross platform compatible

## Requirements  
##### CMake  
##### ImGui
* 'docking' branch on imgui github because the engine implements viewport and docking features
##### OpenGL v4.5 or higher  

# File structure of Bezel engine and sandbox app

.  
+-- include/  
+-- out/  (Output directory on windows (might be called build/ on unix))  
+-- src/  
+-- vendor/  
| ‎‏‏‎ ‎‏‏‎ +-- bezel/	(The Engine library)  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- core/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Timestep.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- GUI/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- ImGui/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- ImGuiBuild.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- ImGuiLayer.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- ImGuiLayer.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- include/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- events/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- AppEvent.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Event.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- KeyEvent.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- MouseEvent.h    
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- renderer/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Buffer.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- CameraController.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- OrthoGraphicCamera.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- RenderAPI.h    
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- RenderCommand.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- RenderContext.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Renderer.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Shader.h    
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Texture.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- VertexArray.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- App.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Core.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Entrypoint.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Input.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- InputCodes.h  
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
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- renderAPI/	(OpenGL implementation of superclasses)
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- OpenGLBuffer.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- OpenGLBuffer.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- OpenGLContext.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- OpenGLContext.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- OpenGLFuncVersion.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- OpenGLFuncVersion.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- OpenGLRenderAPI.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- OpenGLRenderAPI.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- OpenGLShader.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- OpenGLShader.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- OpenGLTexture.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- OpenGLTexture.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- OpenGLVertexArray.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- OpenGLVertexArray.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- src/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- App.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Buffer.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- CameraController.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Layer.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- LayerStack.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Log.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- OrthographicCamera.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- RenderAPI.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- RenderCommand.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Renderer.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Shader.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Texture.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- VertexArray.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- vendor/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- glad/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- glew/  (To be removed)  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- glfw/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- glm/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- imgui/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- spdlog/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- stb/  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Bezel.h  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Precompiled.cpp  
| ‎‏‏‎ ‎‏‏‎ | ‎‏‏‎ ‎‏‏‎ +-- Precompiled.h  
+-- imgui.ini	(GUI config file)
+-- application.cpp	(currently sandbox.cpp)  

NOTE: General header files are in /include directories, while source files are in /src directories.  
Platform specific header and source pairs are togæåether in their respective folders.