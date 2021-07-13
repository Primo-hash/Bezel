#include "bezel/Precompiled.h"
#include "bezel/include/renderer/Shader.h"

#include "bezel/include/renderer/Renderer.h"
#include "bezel/platform/renderAPI/OpenGL/OpenGLShader.h"

namespace Bezel {

	// SHADER CLASS

	/*
		Constructor reads shader programs from file
	*/
	Ref<Shader> Shader::create(const std::string &filepath) {
		switch (Renderer::getAPI()) {
		case RenderAPI::API::None:    BZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(filepath);
		default: BZ_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}

	/*
		Constructor reads shader programs from strings
	*/
	Ref<Shader> Shader::create(const std::string &name, const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::getAPI()) {
		case RenderAPI::API::None:    BZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		default: BZ_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}

	// SHADER LIBRARY CLASS
	
	/*
		Adds shader to library with name
	*/
	void ShaderLibrary::add(const std::string& name, const Ref<Shader>& shader) {
		BZ_CORE_ASSERT(!exists(name), "Shader already exists in library!");
		m_Shaders[name] = shader;
	}

	/*
		Adds shader to library after extracting file name
	*/
	void ShaderLibrary::add(const Ref<Shader>& shader) {
		auto& name = shader->getName();
		add(name, shader);
	}

	/*
		Loads shader from user's specified filepath
		Inserts shader into shader library
	*/
	Bezel::Ref<Shader> ShaderLibrary::load(const std::string& filepath) {
		auto shader = Shader::create(filepath);
		add(shader);
		return shader;
	}

	/*
		Loads shader from user's specified filepath and creates custom name
		Inserts shader into shader library
	*/
	Bezel::Ref<Shader> ShaderLibrary::load(const std::string& name, const std::string& filepath) {
		auto shader = Shader::create(filepath);
		add(name, shader);
		return shader;
	}

	/*
		Returns shader from shader lib map, if it exists
	*/
	Bezel::Ref<Shader> ShaderLibrary::get(const std::string& name)
	{
		BZ_CORE_ASSERT(exists(name), "Shader not found in library!");
		return m_Shaders[name];
	}

	/*
		Returns if a shader already exists in library by name
	*/
	bool ShaderLibrary::exists(const std::string& name) const {
		return m_Shaders.find(name) != m_Shaders.end();
	}
}
