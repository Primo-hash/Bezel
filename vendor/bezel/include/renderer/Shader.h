#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Bezel {

	class Shader {
	private:
		uint32_t m_RendererID;
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void bind() const;
		void unbind() const;

		void addUniformMat4(const std::string& name, const glm::mat4& matrix);
	};

}