#include "dkpch.h"
#include "Renderer.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "ImGuiRenderer.h"
#include "Dark/Core.h"

namespace Dark {

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec2 texCoords;
		float texIndex;
	};

	struct BatchData
	{
		const int MaxQuads = 10000;
		const int MaxVertices = MaxQuads * 4;
		const int MaxIndices = MaxQuads * 6;
		static const int MaxTextures = 32;

		unsigned int QuadCount = 0;
		Vertex* vertsStart = nullptr;
		Vertex* vertsPtr = nullptr;

		float texIndex = 0;
		std::array<std::string, MaxTextures> textures;
	};

	struct RenderData
	{
		Shader TextureShader;
		TextureLibrary texLib = TextureLibrary();

		std::shared_ptr<Window> m_window;

		BatchData batchdata;

		std::shared_ptr<ImGuiRenderer> imGuiRenderer;
	} data;
	
	void Renderer::Init(std::shared_ptr<Window> window)
	{
		data.m_window = window;

		const char* vSource2 = "#version 330 core\n"
			"layout(location = 0) in vec3 aPos; \n"
			"layout(location = 1) in vec3 aColor; \n"
			"layout(location = 2) in vec2 aTexCoord; \n"
			"layout(location = 3) in float aTexIndex; \n"
			"out vec3 ourColor; \n"
			"out vec2 TexCoord; \n"
			"out float TexIndex; \n"
			"uniform int sHeight;\n"
			"uniform int sWidth;\n"
			"void main()\n"
			"{\n"
			"	gl_Position = vec4(((aPos.x*2)-sWidth)/sWidth, ((aPos.y*2)-sHeight)/sHeight, aPos.z, 1.0); \n"
			"	ourColor = aColor; \n"
			"	TexCoord = aTexCoord; \n"
			"   TexIndex = aTexIndex; \n"
			"}\0";
		const char* fSource2 = "#version 330 core\n"
			"out vec4 FragColor; \n"
			"in vec3 ourColor; \n"
			"in vec2 TexCoord; \n"
			"in float TexIndex; \n"
			"uniform sampler2D u_Textures[32]; \n"
			"void main()\n"
			"{\n"
			"	FragColor = texture(u_Textures[int(TexIndex)], TexCoord) * vec4(ourColor, 1.0);\n"
			"}\n\0";

		 data.TextureShader = Shader(std::string(vSource2), std::string(fSource2));

		 glEnable(GL_BLEND);
		 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		 data.imGuiRenderer->Init();
	}

	void Renderer::startRendererCall(int width, int height)
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		data.TextureShader.Use();
		data.TextureShader.setInt("sWidth", width);
		data.TextureShader.setInt("sHeight", height);

		int samplers[data.batchdata.MaxTextures];
		for (int i = 0; i < data.batchdata.MaxTextures; i++)
		{
			samplers[i] = i;
		}
		data.TextureShader.setIntArray("u_Textures", samplers, data.batchdata.MaxTextures);

		data.batchdata.vertsStart = new Vertex[data.batchdata.MaxVertices];
		data.batchdata.vertsPtr = data.batchdata.vertsStart;
		data.batchdata.texIndex = 0.0f;

		data.imGuiRenderer->StartRendererCall();
	}

	void Renderer::endRendererCall()
	{
		flushBatch();
		delete data.batchdata.vertsStart;

		data.imGuiRenderer->EndRendererCall();
	}

	void Renderer::DrawBackDrop(const glm::vec3 color)
	{
		int width = data.m_window->getScreenWidth();
		int height = data.m_window->getScreenHeight();
		Draw2DQuad(glm::vec2(0.0f), glm::vec2(width, height), color);
	}

	void Renderer::DrawBackDrop(std::string texSource)
	{
		int width = data.m_window->getScreenWidth();
		int height = data.m_window->getScreenHeight();
		Draw2DQuad(glm::vec2(0.0f), glm::vec2(width, height), texSource);
	}

	void Renderer::Draw2DQuad(const glm::vec2& corner, glm::vec2 size, glm::vec3 color)
	{
		data.batchdata.vertsPtr->position = { corner.x + size.x, corner.y, 0.0f };
		data.batchdata.vertsPtr->color = color;
		data.batchdata.vertsPtr++;

		data.batchdata.vertsPtr->position = { corner.x + size.x, corner.y + size.y, 0.0f };
		data.batchdata.vertsPtr->color = color;
		data.batchdata.vertsPtr++;

		data.batchdata.vertsPtr->position = { corner.x, corner.y + size.y, 0.0f };
		data.batchdata.vertsPtr->color = color;
		data.batchdata.vertsPtr++;

		data.batchdata.vertsPtr->position = { corner.x, corner.y, 0.0f };
		data.batchdata.vertsPtr->color = color;
		data.batchdata.vertsPtr++;
		data.batchdata.QuadCount++;
	}

	void Renderer::Draw2DQuad(const glm::vec2& corner, glm::vec2 size, std::string texName, glm::vec3 color)
	{
		float textureIndex = 0.0f;
		bool uniqueTexture = true;
		for (int i = 0; i < data.batchdata.texIndex; i++)
		{
			if (data.batchdata.textures[i] == texName) 
			{
				textureIndex = i;
				uniqueTexture = false;
				break;
			}
		}

		if (uniqueTexture)
		{
			textureIndex = data.batchdata.texIndex;
			data.batchdata.textures[data.batchdata.texIndex] = texName;
			data.batchdata.texIndex++;
		}
		//std::cout << textureIndex << " " << texName << " uniqueTexture " << uniqueTexture << std::endl;

		data.batchdata.vertsPtr->position = { corner.x + size.x, corner.y, 0.0f };
		data.batchdata.vertsPtr->color = color;
		data.batchdata.vertsPtr->texCoords = { 1.0f, 0.0f };
		data.batchdata.vertsPtr->texIndex = textureIndex;
		data.batchdata.vertsPtr++;

		data.batchdata.vertsPtr->position = { corner.x + size.x, corner.y + size.y, 0.0f };
		data.batchdata.vertsPtr->color = color;
		data.batchdata.vertsPtr->texCoords = { 1.0f, 1.0f };
		data.batchdata.vertsPtr->texIndex = textureIndex;
		data.batchdata.vertsPtr++;

		data.batchdata.vertsPtr->position = { corner.x, corner.y + size.y, 0.0f };
		data.batchdata.vertsPtr->color = color;
		data.batchdata.vertsPtr->texCoords = { 0.0f, 1.0f };
		data.batchdata.vertsPtr->texIndex = textureIndex;
		data.batchdata.vertsPtr++;

		data.batchdata.vertsPtr->position = { corner.x, corner.y, 0.0f };
		data.batchdata.vertsPtr->color = color;
		data.batchdata.vertsPtr->texCoords = { 0.0f, 0.0f };
		data.batchdata.vertsPtr->texIndex = textureIndex;
		data.batchdata.vertsPtr++;
		data.batchdata.QuadCount++;
	}

	void Renderer::flushBatch()
	{
		for (int i = 0; i < data.batchdata.texIndex; i++)
		{
			std::shared_ptr<Texture> tex = data.texLib.LoadTexture(data.batchdata.textures[i]);
			tex->Bind(i);
		}

		/*int vertsSize = data.verts.size() * sizeof(float);
		float* vertices = &data.verts[0];

		std::vector<unsigned int> inds;
		for (int i = 1; i <= data.quads; i++)
		{
			inds.push_back(0 * i);
			inds.push_back(1 * i);
			inds.push_back(3 * i);
			inds.push_back(1 * i);
			inds.push_back(2 * i);
			inds.push_back(3 * i);
		}
		int indsSize = inds.size() * sizeof(unsigned int);
		unsigned int* indices = &inds[0];*/
		//glm::vec2 corner(0.0f);
		//glm::vec2 size(100.0f);
		//glm::vec3 color(0.5f);
		//float vertices[] = {
		//	corner.x + size.x, corner.y, 0.0f, color.x, color.y, color.z,  // top right
		//	corner.x + size.x, corner.y + size.y, 0.0f, color.x, color.y, color.z,  // bottom right
		//	corner.x, corner.y + size.y, 0.0f, color.x, color.y, color.z,  // bottom left
		//	corner.x, corner.y, 0.0f, color.x, color.y, color.z   // top left 
		//};
		//unsigned int indices[] = {  // note that we start from 0!
		//	0, 1, 3,  // first Triangle
		//	1, 2, 3   // second Triangle
		//};
		//std::cout << sizeof(vertices) << " " << sizeof(indices) << std::endl;

		unsigned int* indices = new unsigned int[data.batchdata.MaxIndices];

		unsigned int offset = 0;
		for (int i = 0; i < data.batchdata.QuadCount * 6; i += 6)
		{
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 3;
			indices[i + 3] = offset + 1;
			indices[i + 4] = offset + 2;
			indices[i + 5] = offset + 3;

			offset += 4;
		}

		unsigned int VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.batchdata.QuadCount*24, indices, GL_DYNAMIC_DRAW);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, (data.batchdata.vertsPtr - data.batchdata.vertsStart)*sizeof(Vertex), data.batchdata.vertsStart, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(8 * sizeof(float)));
		glEnableVertexAttribArray(3);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		//for (int i = 0; i < data.batchdata.texIndex; i++)
		//{
		//	data.texLib.LoadTexture(data.batchdata.textures[i])->Bind(i);
		//}
		
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, data.batchdata.QuadCount * 6, GL_UNSIGNED_INT, 0);

		delete indices;
	}

	void Renderer::AddTexture(std::string texSoure, bool alpha, std::string name)
	{
		data.texLib.AddTexture(texSoure, alpha, name);
	}

}