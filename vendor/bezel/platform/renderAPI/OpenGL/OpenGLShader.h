#pragma once
#include "bezel/include/renderer/Shader.h"

#include <glad/glad.h>	// For testing, to be removed
#include <glm/glm.hpp>


namespace Bezel {

	class EXPORTED OpenGLShader : public Shader {
	private:
		uint32_t m_RendererID;
		std::string m_Name;

		std::string readFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> preProcess(const std::string& source);
		void compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void setInt(const std::string& name, int value) override;
		virtual void setFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void setFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void setMat4(const std::string& name, const glm::mat4& value) override;

		virtual const std::string& getName() const override { return m_Name; }

		void addUniformInt(const std::string& name, int value);

		void addUniformFloat(const std::string& name, float value);
		void addUniformFloat2(const std::string& name, const glm::vec2& value);
		void addUniformFloat3(const std::string& name, const glm::vec3& value);
		void addUniformFloat4(const std::string& name, const glm::vec4& value);

		void addUniformMat3(const std::string& name, const glm::mat3& matrix);
		void addUniformMat4(const std::string& name, const glm::mat4& matrix);
	};

}