#pragma once
#include "Shader.h"
#include "TextureLibrary.h"

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
		static void Init();
		static void startRendererCall(int width, int height);
		static Quad DrawQuad(const VertexAttrib& vert1, const VertexAttrib& vert2,
			const VertexAttrib& vert3, const VertexAttrib& vert4);
		static Quad DrawQuad(const VertexAttrib& corner, glm::vec2 size);
		static Quad DrawQuad(const Quad& quad);
		static Quad DrawTexturedQuad(const VertexAttrib& corner, glm::vec2 size, std::string texSource);
		static Quad DrawTexturedQuad(const VertexAttrib& vert1, const VertexAttrib& vert2,
			const VertexAttrib& vert3, const VertexAttrib& vert4, std::string texSource);
		static void AddTexture(std::string texSoure, bool alpha, std::string name);
	private:
		static Quad privateDrawTexturedQuad(float vertices[], float length, std::string texSource);
		static Quad privateDrawQuad(float vertices[], float length);
	private:
		static Shader Shader1;
		static Shader TextureShader;

		static TextureLibrary texLib;
		static int units;

	};

}