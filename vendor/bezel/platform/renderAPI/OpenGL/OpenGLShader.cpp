#include "bezel/Precompiled.h"
#include "OpenGLShader.h"

#include <filesystem>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

namespace Bezel {

	// HELPER FUNCTIONS

	/*
		Returns GL shader type from string
	*/
	static GLenum ShaderTypeFromString(const std::string& type) {
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;
		BZ_CORE_ASSERT(false, "Unknown shader type when extracting from string!");
		return 0;
	}

	// CLASS FUNCTIONS

	/*
		Constructor reads shader programs from file
	*/
	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string source = readFile(filepath);
		auto shaderSources = preProcess(source);
		compile(shaderSources);

		// Extracting name from file path
		std::filesystem::path path = filepath;
		m_Name = path.stem().string();	// File name stripped of extension (file type)
	}

	/*
		Constructor reads shader programs from strings
	*/
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) : m_Name(name) {
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		compile(sources);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_RendererID);
	}

	/*
		Reads shader language files e.g. .glsl
	*/
	std::string OpenGLShader::readFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in) {
			// ptr to end of file (iterator value now also size of file)
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();	// size of file
			if (size != -1) {
				// resize result string to size of file using ptr iterator
				result.resize(size);
				// ptr back to beginnning
				in.seekg(0, std::ios::beg);
				// read file into string
				in.read(&result[0], size);
				// close file
				in.close();
			}
			else {		// Empty file error handling
				BZ_CORE_ERROR("Could not read from file '{0}'", filepath);
			}
		} else {	// Invalid/Non-existent file path error handling
			BZ_CORE_ERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}

	/*
		Support for '#type' use in glsl, this function parses and returns
		an unordered map containing every #type defined in a glsl file and the
		shader program they define.
		Function continues until end of file.
		Map key as GLenum for compatibility with GL parsing of shader programs.

	*/
	std::unordered_map<GLenum, std::string> OpenGLShader::preProcess(const std::string& source) {
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);		// Beginning of shader #type declaration line
		while (pos != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", pos);		// End of shader #type declaration line
			BZ_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;	// Beginning of shader type name, after #type
			std::string type = source.substr(begin, eol - begin);
			BZ_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol); // Beginning of shader program after shader #type declaration
			BZ_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinePos); // Beginning of next shader #type declaration

			shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}
		return shaderSources;
	}

	/*
		Compiles a shader program using preprocessed shader source code.
		Shader compilation copied from GL wiki.
	*/
	void OpenGLShader::compile(const std::unordered_map<GLenum, std::string>& shaderSources) {
		GLuint program = glCreateProgram();
		BZ_CORE_ASSERT(shaderSources.size() <= 2, "Max 2 shaders supported currently");
		std::array<GLenum, 2> glShaderIDs;	// Changed to array from vector for better performance
		int glShaderIDIndex = 0;

		for (auto& it : shaderSources) {
			GLenum type = it.first;
			const std::string& source = it.second;

			GLuint shader = glCreateShader(type);
			const GLchar* sourceCStr = source.c_str();

			glShaderSource(shader, 1, &sourceCStr, 0);
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE) {	// Error handling
				GLint maxLength = 0;

				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
				glDeleteShader(shader);
				BZ_CORE_ERROR("{0}", infoLog.data());
				BZ_CORE_ASSERT(false, "Shader compilation failure!");
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		m_RendererID = program;

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*) &isLinked);
		if (isLinked == GL_FALSE) { // Linking Error handling
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);

			for (auto id : glShaderIDs)
				glDeleteShader(id);

			BZ_CORE_ERROR("{0}", infoLog.data());
			BZ_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		for (auto id : glShaderIDs) {
			glDetachShader(program, id);
			glDeleteShader(id);
		}
	}

	void OpenGLShader::bind() const {
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::unbind() const {
		glUseProgram(0);
	}

	void OpenGLShader::setInt(const std::string& name, int value) {
		addUniformInt(name, value);
	}

	void OpenGLShader::setFloat(const std::string& name, float value) {
		addUniformFloat(name, value);
	}

	void OpenGLShader::setFloat3(const std::string& name, const glm::vec3& value) {
		addUniformFloat3(name, value);
	}

	void OpenGLShader::setFloat4(const std::string& name, const glm::vec4& value) {
		addUniformFloat4(name, value);
	}

	void OpenGLShader::setMat4(const std::string& name, const glm::mat4& value) {
		addUniformMat4(name, value);
	}

	void OpenGLShader::addUniformInt(const std::string& name, int value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::addUniformFloat(const std::string& name, float value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::addUniformFloat2(const std::string& name, const glm::vec2& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::addUniformFloat3(const std::string& name, const glm::vec3& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::addUniformFloat4(const std::string& name, const glm::vec4& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::addUniformMat3(const std::string& name, const glm::mat3& matrix) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::addUniformMat4(const std::string& name, const glm::mat4& matrix) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}