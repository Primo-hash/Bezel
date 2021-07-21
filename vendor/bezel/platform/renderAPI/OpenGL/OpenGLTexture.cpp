#include "bezel/Precompiled.h"
#include "OpenGLTexture.h"

#include "OpenGLFuncVersion.h"

#include "bezel/vendor/stb/stb_image.h"	// Single header include


namespace Bezel {

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) : m_Width(width), m_Height(height) {
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path(path) {
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		BZ_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;
		
		// OpenGL's internal interpretation of formats
		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4) {		// Image uses RGBA
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3) {	// Image uses RGB
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}
		
		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		BZ_CORE_ASSERT(internalFormat && dataFormat, "Format unsupported!");


		if (OpenGLFuncVersion::getOpenGLVersion() >= 450) {	// Checks to use modern glCreate (> v4.5) or old glGen
			glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		}
		else {
			glGenTextures(1, &m_RendererID);
		}

		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::setData(void* data, uint32_t size) {
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		BZ_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::bind(uint32_t slot) const{
		glBindTextureUnit(slot, m_RendererID);
	}
}