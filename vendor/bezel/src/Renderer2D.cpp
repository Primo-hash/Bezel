#include "bezel/Precompiled.h"
#include "bezel/include/renderer/Renderer2D.h"

#include "bezel/include/renderer/VertexArray.h"
#include "bezel/include/renderer/Shader.h"
#include "bezel/include/renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Bezel {

	struct Renderer2DStorage {
		Ref<VertexArray> quadVertexArray;
		Ref<Shader> textureShader;			// Uploading textures
		Ref<Texture2D> whiteTexture;		// Generating textures/ flat colors
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::init() {
		s_Data = new Renderer2DStorage();
		s_Data->quadVertexArray = VertexArray::create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> squareVB = VertexBuffer::create(squareVertices, sizeof(squareVertices));
		squareVB->setLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
			});
		s_Data->quadVertexArray->addVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB = IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_Data->quadVertexArray->setIndexBuffer(squareIB);

		// Generating texture
		s_Data->whiteTexture = Texture2D::create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;		// Texture color
		s_Data->whiteTexture->setData(&whiteTextureData, sizeof(uint32_t));

		// Uploading texture
		s_Data->textureShader = Shader::create("assets/shaders/Texture.glsl");
		s_Data->textureShader->bind();
		s_Data->textureShader->setInt("u_Texture", 0);
	}

	void Renderer2D::shutdown() {
		delete s_Data;
	}

	void Renderer2D::beginScene(const OrthographicCamera& camera) {
		s_Data->textureShader->bind();
		s_Data->textureShader->setMat4("u_ViewProjection", camera.getViewProjectionMatrix());
	}

	void Renderer2D::endScene() {

	}

	/*
		Draw quad with a 2D position and color
	*/
	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
		drawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	/*
		Draw quad with a 3D position and color
	*/
	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		s_Data->textureShader->setFloat4("u_Color", color);
		s_Data->whiteTexture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->textureShader->setMat4("u_Transform", transform);

		s_Data->quadVertexArray->bind();
		RenderCommand::drawIndexed(s_Data->quadVertexArray);
	}

	/*
		Draw quad with a 2D position and texture
	*/
	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture) {
		drawQuad({ position.x, position.y, 0.0f }, size, texture);
	}

	/*
		Draw quad with a 3D position and texture
	*/
	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture) {
		s_Data->textureShader->setFloat4("u_Color", glm::vec4(1.0f));
		texture->bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->textureShader->setMat4("u_Transform", transform);

		s_Data->quadVertexArray->bind();
		RenderCommand::drawIndexed(s_Data->quadVertexArray);
	}

}