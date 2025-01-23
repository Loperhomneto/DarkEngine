#pragma once

#include "dkpch.h"
#include "Dark/Core.h"
#include "glm.hpp"

namespace Dark
{

	class Renderer2D
	{
	public:
		static void DrawBackDrop(const glm::vec4 color);
		static void DrawBackDrop(const glm::vec3 color);
		static void DrawBackDrop(std::string texSource);
		static void Draw2DQuad(const glm::vec2& corner, glm::vec2 size, glm::vec4 color = glm::vec4(1.0f));
		static void Draw2DQuad(const glm::vec2& corner, glm::vec2 size, glm::vec3 color);
		static void Draw2DQuad(const glm::vec2& corner, glm::vec2 size, std::string texSource, glm::vec4 color = glm::vec4(1.0f));
		static void Draw2DQuad(const glm::vec2& corner, glm::vec2 size, std::string texSource, glm::vec3 color);
		static void AddTexture(std::string texSource, bool alpha, std::string name);
	};

}
