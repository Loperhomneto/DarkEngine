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
	void Renderer2D::AddTexture(std::string texSource, bool alpha, std::string name)
	{
		Renderer::AddTexture(texSource, alpha, name);
	}

	void Renderer2D::AddOrthoCameraController()
	{
		Renderer::AddOrthoCameraController();
	}

	void Renderer2D::AddSpriteSheet(const std::string& texSource, bool alpha, const std::string& name)
	{
		Renderer::AddSpriteSheet(texSource, alpha, name);
	}
	void Renderer2D::DrawSprite(const glm::vec2& corner, const glm::vec2& size, std::string spritesheetName,
		const glm::vec2& spriteCoords, const glm::vec2& spriteSize = glm::vec2(1.0f), glm::vec4 color = glm::vec4(1.0f))
	{
		Renderer::DrawSprite(corner, size, spritesheetName, spriteCoords, spriteSize, color);
	}
	void Renderer2D::DrawSprite(const glm::vec2& corner, const glm::vec2& size, std::string spritesheetName,
		const glm::vec2& spriteCoords, const glm::vec2& spriteSize, glm::vec3 color)
	{
		Renderer:DrawSprite(corner, size, spritesheetName, spriteCoords, spriteSize, color);
	}


}