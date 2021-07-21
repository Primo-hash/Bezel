#pragma once

#include "bezel/include/renderer/Texture.h"

#include <glad/glad.h>

namespace Bezel {

	class OpenGLTexture2D : public Texture2D {
	private:
		GLenum m_InternalFormat, m_DataFormat;

		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual void setData(void* data, uint32_t size) override;

		virtual uint32_t getWidth() const override { return m_Width; }
		virtual uint32_t getHeight() const override { return m_Height; }

		virtual void bind(uint32_t slot = 0) const override;
		void selectTextureFunc();
	};

}