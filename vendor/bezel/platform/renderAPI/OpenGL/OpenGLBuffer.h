#pragma once

#include "bezel/include/renderer/Buffer.h"

namespace Bezel {

	class OpenGLVertexBuffer : public VertexBuffer {
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual const BufferLayout& getLayout() const override { return m_Layout; }
		virtual void setLayout(const BufferLayout& layout) override { m_Layout = layout; }
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void bind() const;
		virtual void unbind() const;

		virtual uint32_t getCount() const { return m_Count; }
	};

}
