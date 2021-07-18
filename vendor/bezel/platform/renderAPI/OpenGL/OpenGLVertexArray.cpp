#include "bezel/Precompiled.h"
#include "OpenGLVertexArray.h"

#include "OpenGLFuncVersion.h"

#include <glad/glad.h>
#include <cstdint>

namespace Bezel {

	static GLenum shaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type) {
		case Bezel::ShaderDataType::Float:    return GL_FLOAT;
		case Bezel::ShaderDataType::Float2:   return GL_FLOAT;
		case Bezel::ShaderDataType::Float3:   return GL_FLOAT;
		case Bezel::ShaderDataType::Float4:   return GL_FLOAT;
		case Bezel::ShaderDataType::Mat3:     return GL_FLOAT;
		case Bezel::ShaderDataType::Mat4:     return GL_FLOAT;
		case Bezel::ShaderDataType::Int:      return GL_INT;
		case Bezel::ShaderDataType::Int2:     return GL_INT;
		case Bezel::ShaderDataType::Int3:     return GL_INT;
		case Bezel::ShaderDataType::Int4:     return GL_INT;
		case Bezel::ShaderDataType::Bool:     return GL_BOOL;
		default: BZ_CORE_ASSERT(false, "Unknown ShaderDataType!"); return 0;
		}
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		if (OpenGLFuncVersion::getOpenGLVersion() >= 450) {	// Checks to use modern glCreate (> v4.5) or old glGen
			// Uses glCreate*
			#define BZ_OPENGL_DEFINE_VERTEX_ARRAYS(...)::glCreateVertexArrays(__VA_ARGS__)
		}
		else {
			// Uses glGen*
			#define BZ_OPENGL_DEFINE_VERTEX_ARRAYS(...)::glGenVertexArrays(__VA_ARGS__)
		}
		BZ_OPENGL_DEFINE_VERTEX_ARRAYS(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::bind() const {
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::unbind() const {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
		// Checks that addVertexBuffer is not being called before setLayout
		BZ_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->bind();

		const auto& layout = vertexBuffer->getLayout();	// Get premade layout
		for (const auto& element : layout) {	// Send layout specs for every ShaderDataType to GL 
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(m_VertexBufferIndex,
				element.GetComponentCount(),
				shaderDataTypeToOpenGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.getStride(),
				(const void*)element.offset);	// casting to uintptr_t first avoids int to void* size discrepancy
			m_VertexBufferIndex++;	// Increase index created to avoid buffers stacking.
		}

		m_VertexBuffers.push_back(vertexBuffer);					// Add to current collection of Buffers
	}

	void OpenGLVertexArray::setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
		// Bind Indexes for current Array
		glBindVertexArray(m_RendererID);
		indexBuffer->bind();

		m_IndexBuffer = indexBuffer;
	}

	// EXPERIMENTAL

	/*
		Defines suitable OpenGL vertex array creation functions based on version
	*/
	void OpenGLVertexArray::selectVertexArrayFunc() {
		if (OpenGLFuncVersion::getOpenGLVersion() >= 450) {	// Checks to use modern glCreate (> v4.5) or old glGen
			// Uses glCreate*
			#define BZ_OPENGL_DEFINE_VERTEX_ARRAYS(...)::glCreateVertexArrays(__VA_ARGS__)
		}
		else {
			// Uses glGen*
			#define BZ_OPENGL_DEFINE_VERTEX_ARRAYS(...)::glGenVertexArrays(__VA_ARGS__)
		}
	}
}
