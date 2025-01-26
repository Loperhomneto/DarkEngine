#include "dkpch.h"
#include "Renderer.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "ImGuiRenderer.h"
#include "Dark/Core.h"
#include "Shader.h"
#include "OrthoCameraController.h"

namespace Dark {

	struct Vertex
	{
		glm::vec3 position;
		glm::vec4 color;
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

		unsigned int* indicesStart = nullptr;

		float texIndex = 1;
		std::array<std::string, MaxTextures> textures;
	};

	struct RenderData
	{
		Shader TextureShader;
		TextureLibrary texLib = TextureLibrary();

		SpritesheetLibrary spritesheetTexLib = SpritesheetLibrary();
		unsigned int spritesheets = 0;
		unsigned int spriteIndex = 0;

		std::shared_ptr<Window> m_window;

		BatchData batchdata;

		std::shared_ptr<ImGuiRenderer> imGuiRenderer;

		bool isCameraController = false;
		std::shared_ptr<OrthoCameraController> orthoCameraController;
	} data;
	
	void Renderer::Init(std::shared_ptr<Window> window)
	{
		data.m_window = window;

		const char* vSource2 = "#version 330 core\n"
			"layout(location = 0) in vec3 aPos; \n"
			"layout(location = 1) in vec4 aColor; \n"
			"layout(location = 2) in vec2 aTexCoord; \n"
			"layout(location = 3) in float aTexIndex; \n"
			"out vec4 ourColor; \n"
			"out vec2 TexCoord; \n"
			"out float TexIndex; \n"
			"uniform int sHeight;\n"
			"uniform int sWidth;\n"
			"uniform mat4 sViewProjectionMatrix;"
			"void main()\n"
			"{\n"
			"	gl_Position = sViewProjectionMatrix * vec4(((aPos.x*2)-sWidth)/sWidth, ((aPos.y*2)-sHeight)/sHeight, aPos.z, 1.0); \n"
			"	ourColor = aColor; \n"
			"	TexCoord = aTexCoord; \n"
			"   TexIndex = aTexIndex; \n"
			"}\0";
		const char* fSource2 = "#version 330 core\n"
			"out vec4 FragColor; \n"
			"in vec4 ourColor; \n"
			"in vec2 TexCoord; \n"
			"in float TexIndex; \n"
			"uniform sampler2D u_Textures[32]; \n"
			"void main()\n"
			"{\n"
			"	FragColor = texture(u_Textures[int(TexIndex)], TexCoord) * ourColor;\n"
			"}\n\0";

		 data.TextureShader = Shader(std::string(vSource2), std::string(fSource2));

		 glEnable(GL_BLEND);
		 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		 data.imGuiRenderer->Init();

		 data.batchdata.vertsStart = new Vertex[data.batchdata.MaxVertices];
		 data.batchdata.indicesStart = new unsigned int[data.batchdata.MaxIndices];

		 unsigned int whiteTextureData = 0xffffffff;
		 std::shared_ptr<Texture> whiteTexture = std::make_shared<Texture>(1, 1, &whiteTextureData);
		 data.texLib.AddTexture(whiteTexture, "whiteTexture");
		 data.batchdata.textures[0] = "whiteTexture";
	}

	void Renderer::DeInit()
	{
		delete[] data.batchdata.vertsStart;
		delete[] data.batchdata.indicesStart;
		data.imGuiRenderer->Shutdown();
	}

	void Renderer::startRendererCall(int width, int height)
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		data.TextureShader.Use();
		data.TextureShader.setInt("sWidth", width);
		data.TextureShader.setInt("sHeight", height);

		if (data.isCameraController)
		{
			data.TextureShader.setMat4("sViewProjectionMatrix", data.orthoCameraController->getViewProjectionMatrix());
		}
		else
		{
			data.TextureShader.setMat4("sViewProjectionMatrix", glm::mat4(1.0f));
		}

		int samplers[data.batchdata.MaxTextures];
		for (int i = 0; i < data.batchdata.MaxTextures; i++)
		{
			samplers[i] = i;
		}
		data.TextureShader.setIntArray("u_Textures", samplers, data.batchdata.MaxTextures);

		data.batchdata.vertsPtr = data.batchdata.vertsStart;
		data.batchdata.texIndex = 1.0f;
		data.batchdata.QuadCount = 0;

		data.imGuiRenderer->StartRendererCall();
	}

	void Renderer::endRendererCall()
	{
		flushBatch();

		data.imGuiRenderer->EndRendererCall();
	}

	void Renderer::DrawBackDrop(const glm::vec3 color)
	{
		Renderer::DrawBackDrop(glm::vec4(color.x, color.y, color.z, 1.0f));
	}

	void Renderer::DrawBackDrop(const glm::vec4 color)
	{
		int width = data.m_window->getScreenWidth();
		int height = data.m_window->getScreenHeight();
		Draw2DQuad(glm::vec2(0.0f), glm::vec2(width, height), color);
	}

	void Renderer::DrawBackDrop(const std::string& texSource)
	{
		int width = data.m_window->getScreenWidth();
		int height = data.m_window->getScreenHeight();
		Draw2DQuad(glm::vec2(0.0f), glm::vec2(width, height), texSource);
	}

	void Renderer::Draw2DQuad(const glm::vec2& corner, const glm::vec2& size, glm::vec3 color)
	{
		Renderer::Draw2DQuad(corner, size, glm::vec4(color.x, color.y, color.z, 1.0f));
	}

	void Renderer::Draw2DQuad(const glm::vec2& corner, const glm::vec2& size, glm::vec4 color)
	{
		float textureIndex = 0.0f;

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

	void Renderer::Draw2DQuad(const glm::vec2& corner, const glm::vec2& size, const std::string& texName, glm::vec3 color)
	{
		Renderer::Draw2DQuad(corner, size, texName, glm::vec4(color.x, color.y, color.z, 1.0f));
	}

	void Renderer::Draw2DQuad(const glm::vec2& corner, const glm::vec2& size, const std::string& texName, glm::vec4 color)
	{
		float textureIndex = 1.0f;
		bool uniqueTexture = true;
		for (int i = 1; i < data.batchdata.texIndex; i++)
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
			data.batchdata.textures[textureIndex] = texName;
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

		unsigned int offset = 0;
		for (int i = 0; i < (data.batchdata.QuadCount) * 6; i += 6)
		{
			data.batchdata.indicesStart[i + 0] = offset + 0;
			data.batchdata.indicesStart[i + 1] = offset + 1;
			data.batchdata.indicesStart[i + 2] = offset + 3;
			data.batchdata.indicesStart[i + 3] = offset + 1;
			data.batchdata.indicesStart[i + 4] = offset + 2;
			data.batchdata.indicesStart[i + 5] = offset + 3;

			offset += 4;
		}

		unsigned int VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.batchdata.QuadCount*24, data.batchdata.indicesStart, GL_DYNAMIC_DRAW);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, (data.batchdata.vertsPtr - data.batchdata.vertsStart)*sizeof(Vertex), data.batchdata.vertsStart, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(7 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(9 * sizeof(float)));
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
		//Logger::info(std::to_string(VAO).c_str());
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, data.batchdata.QuadCount * 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		GLuint buffers[] = { VBO, EBO };
		glDeleteBuffers(2, buffers);
		unsigned int vertexArraysBuffer[] = {VAO};
		glDeleteVertexArrays(1, vertexArraysBuffer);
	}

	void Renderer::AddTexture(const std::string& texSource, bool alpha, const std::string& name)
	{
		data.texLib.AddTexture(texSource, alpha, name);
	}

	void Renderer::AddSpriteSheet(const std::string& texSource, bool alpha, const std::string& name, unsigned int width, unsigned int height, unsigned int spriteWidth, unsigned int spriteHeight)
	{
		data.spritesheetTexLib.AddSpritesheet(texSource, alpha, name, width, height, spriteWidth, spriteHeight);
	}
	
	void Renderer::DrawSprite(const glm::vec2& corner, const glm::vec2& size, unsigned int spriteWidth, unsigned int spriteHeight, unsigned int x, unsigned int y, std::string spritesheetName, glm::vec3 color)
	{
		DrawSprite(corner, size, spriteWidth, spriteHeight, x, y, spritesheetName, glm::vec4(color.x, color.y, color.z, 1.0f));
	}

	void Renderer::DrawSprite(const glm::vec2& corner, const glm::vec2& size, unsigned int spriteWidth, unsigned int spriteHeight, unsigned int x, unsigned int y, std::string spritesheetName, glm::vec4 color)
	{
		float textureIndex = 0.0f;
		bool uniqueTexture = true;
		for (int i = 0; i < data.batchdata.texIndex; i++)
		{
			if (data.batchdata.textures[i] == spritesheetName)
			{
				textureIndex = i;
				uniqueTexture = false;
				break;
			}
		}

		if (uniqueTexture)
		{
			textureIndex = data.batchdata.texIndex;
			data.batchdata.textures[textureIndex] = spritesheetName;
			data.batchdata.texIndex++;
			data.spritesheets++;
		}

		std::shared_ptr<SpriteSheet> spritesheet = data.spritesheetTexLib.LoadSpritesheet(spritesheetName);
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

	void Renderer::AddOrthoCameraController()
	{
		if (!data.isCameraController)
		{
			data.isCameraController = true;

			data.orthoCameraController = std::make_shared<OrthoCameraController>();
		}
	}

	void Renderer::OnUpdate(TimeStep ts)
	{
		if (data.isCameraController)
		{
			data.orthoCameraController->OnUpdate(ts);
		}
	}

	void Renderer::OnEvent(Event& e)
	{
		if (data.isCameraController)
		{
			data.orthoCameraController->OnEvent(e);
		}
	}

}