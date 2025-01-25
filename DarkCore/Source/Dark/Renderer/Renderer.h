#pragma once
#include "TextureLibrary.h"
#include "Dark/Window.h"
#include "Dark/Core.h"
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
		static void DrawBackDrop(std::string texSource);
		static void Draw2DQuad(const glm::vec2& corner, glm::vec2 size, glm::vec4 color = glm::vec4(1.0f));
		static void Draw2DQuad(const glm::vec2& corner, glm::vec2 size, glm::vec3 color);
		static void Draw2DQuad(const glm::vec2& corner, glm::vec2 size, std::string texSource, glm::vec4 color = glm::vec4(1.0f));
		static void Draw2DQuad(const glm::vec2& corner, glm::vec2 size, std::string texSource, glm::vec3 color);
		
		static void AddTexture(std::string texSource, bool alpha, std::string name);

		static void AddOrthoCameraController();
		static void OnUpdate(TimeStep ts);
		static void OnEvent(Event& e);
	private:
		static void flushBatch();
	};

}