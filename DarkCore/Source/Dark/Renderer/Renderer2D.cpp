#include "dkpch.h"
#include "Renderer2D.h"
#include "Renderer.h"

namespace Dark
{

	void Renderer2D::DrawBackDrop(const glm::vec4 color)
	{
		Renderer::DrawBackDrop(color);
	}

	void Renderer2D::DrawBackDrop(const glm::vec3 color)
	{
		Renderer::DrawBackDrop(color);
	}

	void Renderer2D::DrawBackDrop(std::string texSource)
	{
		Renderer::DrawBackDrop(texSource);
	}

	void Renderer2D::Draw2DQuad(const glm::vec3& corner, glm::vec2 size, glm::vec4 color)
	{
		Renderer::Draw2DQuad(corner, size, color);
	}

	void Renderer2D::Draw2DQuad(const glm::vec3& corner, glm::vec2 size, glm::vec3 color)
	{
		Renderer::Draw2DQuad(corner, size, color);
	}

	void Renderer2D::Draw2DQuad(const glm::vec3& corner, glm::vec2 size, std::string texSource, glm::vec4 color)
	{
		Renderer::Draw2DQuad(corner, size, color);
	}

	void Renderer2D::Draw2DQuad(const glm::vec3& corner, glm::vec2 size, std::string texSource, glm::vec3 color)
	{
		Renderer::Draw2DQuad(corner, size, color);
	}

	void Renderer2D::Draw2DQuad(const glm::vec2& corner, glm::vec2 size, glm::vec4 color)
	{
		Renderer::Draw2DQuad(corner, size, color);
	}

	void Renderer2D::Draw2DQuad(const glm::vec2& corner, glm::vec2 size, glm::vec3 color)
	{
		Renderer::Draw2DQuad(corner, size, color);
	}

	void Renderer2D::Draw2DQuad(const glm::vec2& corner, glm::vec2 size, std::string texSource, glm::vec4 color)
	{
		Renderer::Draw2DQuad(corner, size, texSource, color);
	}

	void Renderer2D::Draw2DQuad(const glm::vec2& corner, glm::vec2 size, std::string texSource, glm::vec3 color)
	{
		Renderer::Draw2DQuad(corner, size, texSource, color);
	}

	void Renderer2D::Draw2DRotatedQuad(const glm::vec3& center, const glm::vec2& size, float rotation, glm::vec4 color)
	{
		Renderer::Draw2DRotatedQuad(center, size, rotation, color);
	}

	void Renderer2D::Draw2DRotatedQuad(const glm::vec3& center, const glm::vec2& size, float rotation, glm::vec3 color)
	{
		Renderer::Draw2DRotatedQuad(center, size, rotation, color);
	}

	void Renderer2D::Draw2DRotatedQuad(const glm::vec3& center, const glm::vec2& size, float rotation, const std::string& texSource, glm::vec4 color)
	{
		Renderer::Draw2DRotatedQuad(center, size, rotation, texSource, color);
	}

	void Renderer2D::Draw2DRotatedQuad(const glm::vec3& center, const glm::vec2& size, float rotation, const std::string& texSource, glm::vec3 color)
	{
		Renderer::Draw2DRotatedQuad(center, size, rotation, texSource, color);
	}

	void Renderer2D::Draw2DRotatedQuad(const glm::vec2& center, const glm::vec2& size, float rotation, glm::vec4 color /*= glm::vec4(1.0f)*/)
	{
		Renderer::Draw2DRotatedQuad(center, size, rotation, color);
	}

	void Renderer2D::Draw2DRotatedQuad(const glm::vec2& center, const glm::vec2& size, float rotation, glm::vec3 color)
	{
		Renderer::Draw2DRotatedQuad(center, size, rotation, color);
	}

	void Renderer2D::Draw2DRotatedQuad(const glm::vec2& center, const glm::vec2& size, float rotation, const std::string& texSource, glm::vec4 color /*= glm::vec4(1.0f)*/)
	{
		Renderer::Draw2DRotatedQuad(center, size, rotation, texSource, color);
	}

	void Renderer2D::Draw2DRotatedQuad(const glm::vec2& center, const glm::vec2& size, float rotation, const std::string& texSource, glm::vec3 color)
	{
		Renderer::Draw2DRotatedQuad(center, size, rotation, texSource, color);
	}

	void Renderer2D::AddTexture(const std::string& texName, bool alpha, std::string name)
	{
		Renderer::AddTexture(texName, alpha, name);
	}

	void Renderer2D::AddOrthoCameraController()
	{
		Renderer::AddOrthoCameraController();
	}

	bool Renderer2D::ValidateTexture(const std::string& texName)
	{
		return Renderer::ValidateTexture(texName);
	}

	void Renderer2D::AddSpritesheet(const std::string& texSource, bool alpha, const std::string& name, const glm::vec2& spriteSize)
	{
		Renderer::AddSpritesheet(texSource, alpha, name, spriteSize);
	}
	void Renderer2D::DrawSprite(const glm::vec2& corner, const glm::vec2& size, std::string spritesheetName,
		const glm::vec2& spriteCoords, const glm::vec2& spriteSize, glm::vec4 color)
	{
		Renderer::DrawSprite(corner, size, spritesheetName, spriteCoords, spriteSize, color);
	}
	void Renderer2D::DrawSprite(const glm::vec2& corner, const glm::vec2& size, std::string spritesheetName,
		const glm::vec2& spriteCoords, const glm::vec2& spriteSize, glm::vec3 color)
	{
		Renderer:DrawSprite(corner, size, spritesheetName, spriteCoords, spriteSize, color);
	}


	void Renderer2D::updateFramebuffer(glm::vec2 size)
	{
		Renderer::updateFramebuffer(size);
	}

}