#pragma once
#include "Shader.h"
#include "TextureLibrary.h"
#include "Dark/Window.h"
#include <memory>

namespace Dark {

	struct VertexAttrib
	{
		VertexAttrib(glm::vec2 POS, glm::vec3 COLOR = glm::vec3(1.0f))
		{
			pos = POS;
			color = COLOR;
		}

		glm::vec2 pos;
		glm::vec3 color;
	};

	struct Quad
	{
		int VAO = 0;
		int texID = 0;
	};

	class Renderer
	{
	public:
		static void Init(std::shared_ptr<Window> window);
		static void startRendererCall(int width, int height);
		static void endRendererCall();
		static Quad DrawBackDrop(const glm::vec3 color);
		static Quad DrawBackDrop(std::string texSource);
		static Quad Draw2DQuad(const glm::vec2& corner, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f));
		static Quad Draw2DQuad(const Quad& quad);
		static Quad Draw2DQuad(const glm::vec2& corner, glm::vec2 size, std::string texSource, glm::vec3 color = glm::vec3(1.0f));
		static void AddTexture(std::string texSoure, bool alpha, std::string name);
	private:
		static Quad privateDrawQuad(float vertices[], float length);
		static Quad privateDrawTexturedQuad(float vertices[], float length, std::string texSource);
	private:
		static std::vector<float> verts;
		static int quads;
		static Shader Shader1;
		static Shader TextureShader;

		static TextureLibrary texLib;
		static int units;

		static std::shared_ptr<Window> m_window;

	};

}