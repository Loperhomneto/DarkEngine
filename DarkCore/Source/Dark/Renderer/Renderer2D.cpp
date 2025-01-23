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

}