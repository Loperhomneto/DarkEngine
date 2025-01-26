#pragma once
#include "TextureLibrary.h"
#include "Dark/Window.h"
#include "Dark/Core.h"
#include "Dark/TimeStep.h"
#include "glm.hpp"

namespace Dark {

	class Renderer
	{
	public:
		static void Init(std::shared_ptr<Window> window);
		static void DeInit();
		static void startRendererCall(int width, int height);
		static void endRendererCall();
		static void DrawBackDrop(const glm::vec4 color);
		static void DrawBackDrop(const glm::vec3 color);
		static void DrawBackDrop(const std::string& texSource);
		static void Draw2DQuad(const glm::vec2& corner, const glm::vec2& size, glm::vec4 color = glm::vec4(1.0f));
		static void Draw2DQuad(const glm::vec2& corner, const glm::vec2& size, glm::vec3 color);
		static void Draw2DQuad(const glm::vec2& corner, const glm::vec2& size, const std::string& texSource, glm::vec4 color = glm::vec4(1.0f));
		static void Draw2DQuad(const glm::vec2& corner, const glm::vec2& size, const std::string& texSource, glm::vec3 color);
		
		static void AddTexture(const std::string& texSource, bool alpha, const std::string& name);

		static void AddSpriteSheet(const std::string& texSource, bool alpha, const std::string& name, const glm::vec2& spritesheetSize, const glm::vec2& spriteSize);
		static void DrawSprite(const glm::vec2& corner, const glm::vec2& size, std::string spritesheetSource, 
			const glm::vec2& spriteCoords, const glm::vec2& spriteSize = glm::vec2(1.0f), glm::vec4 color = glm::vec4(1.0f));
		static void DrawSprite(const glm::vec2& corner, const glm::vec2& size, std::string spritesheetSource, 
			const glm::vec2& spriteCoords, const glm::vec2& spriteSize, glm::vec3 color);

		static void AddOrthoCameraController();
		static void OnUpdate(TimeStep ts);
		static void OnEvent(Event& e);
	private:
		static void flushBatch();
	};

}