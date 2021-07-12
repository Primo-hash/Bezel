#include "bezel/Precompiled.h"
#include "OpenGLBuffer.h"

#include "OpenGLFuncVersion.h"

#include <glad/glad.h>

/*
	Vertex and index buffering specific to OpenGL
*/

namespace Bezel {

	/*
		VERTEX BUFFER DEF
	*/
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
		if (OpenGLFuncVersion::getOpenGLVersion() >= 450) {	// Checks to use modern glCreate (> v4.5) or old glGen
			// Uses glCreate*
			#define BZ_OPENGL_DEFINE_BUFFERS(...)::glCreateBuffers(__VA_ARGS__)
		} else {
			// Uses glGen*
			#define BZ_OPENGL_DEFINE_BUFFERS(...)::glGenBuffers(__VA_ARGS__)
		}
		BZ_OPENGL_DEFINE_BUFFERS(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/*
		INDEX BUFFER DEF
	*/
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : m_Count(count) {
		if (OpenGLFuncVersion::getOpenGLVersion() >= 450) {	// Checks to use modern glCreate (> v4.5) or old glGen
			// Uses glCreate*
			#define BZ_OPENGL_DEFINE_BUFFERS(...)::glCreateBuffers(__VA_ARGS__)
		} else {
			// Uses glGen*
			#define BZ_OPENGL_DEFINE_BUFFERS(...)::glGenBuffers(__VA_ARGS__)
		}
		BZ_OPENGL_DEFINE_BUFFERS(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer() {
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	/*
		Defines suitable OpenGL buffer creation functions based on version
	*/
	void selectBufferFunc() {
		if (OpenGLFuncVersion::getOpenGLVersion() >= 450) {	// Checks to use modern glCreate (> v4.5) or old glGen
			// Uses glCreate*
			#define BZ_OPENGL_DEFINE_BUFFERS(...)::glCreateBuffers(__VA_ARGS__)
		}
		else {
			// Uses glGen*
			#define BZ_OPENGL_DEFINE_BUFFERS(...)::glGenBuffers(__VA_ARGS__)
		}
	}
}