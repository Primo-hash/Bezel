#pragma once

#include <string>

namespace Bezel {

	class Shader {
	private:
		uint32_t m_RendererID;
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void bind() const;
		void unbind() const;
	};

}