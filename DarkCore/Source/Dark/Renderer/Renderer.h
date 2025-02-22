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
		static void Init(std::shared_ptr<Window> window, bool useFrameBuffer);
		static void Shutdown();

		static void startRendererCall();
		static void endRendererCall();
		static void endImguiRendererCall();

		static unsigned int getColorAttachment();

		//Backgrounds (Deprecated do not use)
		static void DrawBackDrop(const glm::vec4 color);
		static void DrawBackDrop(const glm::vec3 color);
		static void DrawBackDrop(const std::string& texSource);

		//Flat colored quads and textured quads
		static void Draw2DQuad(const glm::vec3& corner, const glm::vec2& size, glm::vec4 color = glm::vec4(1.0f));
		static void Draw2DQuad(const glm::vec3& corner, const glm::vec2& size, glm::vec3 color);
		static void Draw2DQuad(const glm::vec3& corner, const glm::vec2& size, const std::string& texSource, glm::vec4 color = glm::vec4(1.0f));
		static void Draw2DQuad(const glm::vec3& corner, const glm::vec2& size, const std::string& texSource, glm::vec3 color);
		static void Draw2DQuad(const glm::vec2& corner, const glm::vec2& size, glm::vec4 color = glm::vec4(1.0f));
		static void Draw2DQuad(const glm::vec2& corner, const glm::vec2& size, glm::vec3 color);
		static void Draw2DQuad(const glm::vec2& corner, const glm::vec2& size, const std::string& texSource, glm::vec4 color = glm::vec4(1.0f));
		static void Draw2DQuad(const glm::vec2& corner, const glm::vec2& size, const std::string& texSource, glm::vec3 color);

		//Drawing rotated quads with flat colors and textures
		static void Draw2DRotatedQuad(const glm::vec3& center, const glm::vec2& size, float rotation, glm::vec4 color = glm::vec4(1.0f));
		static void Draw2DRotatedQuad(const glm::vec3& center, const glm::vec2& size, float rotation, glm::vec3 color);
		static void Draw2DRotatedQuad(const glm::vec3& center, const glm::vec2& size, float rotation, const std::string& texSource, glm::vec4 color = glm::vec4(1.0f));
		static void Draw2DRotatedQuad(const glm::vec3& center, const glm::vec2& size, float rotation, const std::string& texSource, glm::vec3 color);
		static void Draw2DRotatedQuad(const glm::vec2& center, const glm::vec2& size, float rotation, glm::vec4 color = glm::vec4(1.0f));
		static void Draw2DRotatedQuad(const glm::vec2& center, const glm::vec2& size, float rotation, glm::vec3 color);
		static void Draw2DRotatedQuad(const glm::vec2& center, const glm::vec2& size, float rotation, const std::string& texSource, glm::vec4 color = glm::vec4(1.0f));
		static void Draw2DRotatedQuad(const glm::vec2& center, const glm::vec2& size, float rotation, const std::string& texSource, glm::vec3 color);
		
		//Adding texture to texture lib
		static void AddTexture(const std::string& texName, bool alpha, const std::string& name);
		static bool ValidateTexture(const std::string& texName);

		//Drawing and adding sprite sheets
		static void AddSpritesheet(const std::string& texSource, bool alpha, const std::string& name, const glm::vec2& spriteSize);
		static void DrawSprite(const glm::vec2& center, const glm::vec2& size, std::string spritesheetName, const glm::vec2& spriteCoords, const glm::vec2& spriteSize = glm::vec2(1.0f), float rotation = 90.0f, glm::vec4 color = glm::vec4(1.0f));
		static void DrawSprite(const glm::vec2& center, const glm::vec2& size, std::string spritesheetName, const glm::vec2& spriteCoords, const glm::vec2& spriteSize, float rotation, glm::vec3 color);
		static void DrawSprite(const glm::vec3& center, const glm::vec2& size, std::string spritesheetName, const glm::vec2& spriteCoords, const glm::vec2& spriteSize = glm::vec2(1.0f), float rotation = 90.0f, glm::vec4 color = glm::vec4(1.0f));
		static void DrawSprite(const glm::vec3& center, const glm::vec2& size, std::string spritesheetName, const glm::vec2& spriteCoords, const glm::vec2& spriteSize, float rotation, glm::vec3 color);

		static void updateFramebuffer(glm::vec2 size);

		//Updating and using the camera
		static void AddOrthoCameraController();
		static void OnUpdate(TimeStep ts);
		static void OnEvent(Event& e);
		static void OnWindowResize(WindowResizeEvent& e);
	private:
		static void flushBatch();

		static void createFrameBuffer(glm::vec2 size);

		static float getTextureIndex(const std::string& texName);

		static void setVertices(const glm::vec3& center, const glm::vec2& size, const glm::vec4& color, float rotation, float textureIndex, glm::vec2 texCoords[4]);
		static void setVertices(const glm::vec2& center, const glm::vec2& size, const glm::vec4& color, float rotation, float textureIndex, glm::vec2 texCoords[4]);
		static void setVertices(const glm::vec3& center, const glm::vec2& size, const glm::vec4& color, float rotation = 0.0f, float textureIndex = 0.0f);
		static void setVertices(const glm::vec2& center, const glm::vec2& size, const glm::vec4& color, float rotation = 0.0f, float textureIndex = 0.0f);
	};

}