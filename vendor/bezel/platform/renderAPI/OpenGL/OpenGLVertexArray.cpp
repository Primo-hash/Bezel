#include "bezel/Precompiled.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

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
		glCreateVertexArrays(1, &m_RendererID);
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

	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
		// Checks that addVertexBuffer is not being called before setLayout
		BZ_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->getLayout();	// Get premade layout
		for (const auto& element : layout) {	// Send layout specs for every ShaderDataType to GL 
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				shaderDataTypeToOpenGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.getStride(),
				reinterpret_cast<const void*>(element.offset));
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);	// Add to current collection of Buffers
	}

	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
		// Bind Indexes for current Array
		glBindVertexArray(m_RendererID);
		indexBuffer->bind();

		m_IndexBuffer = indexBuffer;
	}
}
