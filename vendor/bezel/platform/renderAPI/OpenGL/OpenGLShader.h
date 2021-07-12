#pragma once

#include "bezel/include/renderer/Shader.h"
#include <glm/glm.hpp>

namespace Bezel {

	class EXPORTED OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void bind() const override;
		virtual void unbind() const override;

		void addUniformInt(const std::string& name, int value);

		void addUniformFloat(const std::string& name, float value);
		void addUniformFloat2(const std::string& name, const glm::vec2& value);
		void addUniformFloat3(const std::string& name, const glm::vec3& value);
		void addUniformFloat4(const std::string& name, const glm::vec4& value);

		void addUniformMat3(const std::string& name, const glm::mat3& matrix);
		void addUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		uint32_t m_RendererID;
	};

}