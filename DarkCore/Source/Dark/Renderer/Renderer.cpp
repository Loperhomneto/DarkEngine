#include "dkpch.h"
#include "Renderer.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "ImGuiRenderer.h"
#include "Dark/Core.h"
#include "Shader.h"
#include "Dark/Input.h"
//Remove later
#include "imgui.h"
#include "OrthoCameraController.h"
#include "gtc/matrix_transform.hpp"
#include <iostream>

namespace Dark {
	

	//Render data
	struct Spritesheet
	{
		glm::vec2 spriteSize;

		Spritesheet(const glm::vec2& spriteSize)
		{
			this->spriteSize = spriteSize;
		}
	};

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

		std::shared_ptr<Window> m_window;

		BatchData batchdata;

		std::shared_ptr<ImGuiRenderer> imGuiRenderer;

		bool isCameraController = false;
		std::shared_ptr<OrthoCameraController> orthoCameraController;

		std::unordered_map<std::string, std::shared_ptr<Spritesheet>> spritesheets;

		unsigned int frameBufferRendererID = 0;
		unsigned int colorAttachmentRendererID = 0;
		unsigned int depthAttactmentRendererID = 0;

		bool usingFrameBuffer = false;
		bool updateQueueFrameBuffer = true;
		glm::vec2 framebufferSize = glm::vec2(1280, 720);
	} data;
	

	//Renderer initiliaztion and deinilization
	void Renderer::Init(std::shared_ptr<Window> window, bool useFrameBuffer)
	{
		data.m_window = window;
		data.usingFrameBuffer = useFrameBuffer;

		const char* vSource2 = "#version 330 core\n"
			"layout(location = 0) in vec3 aPos; \n"
			"layout(location = 1) in vec4 aColor; \n"
			"layout(location = 2) in vec2 aTexCoord; \n"
			"layout(location = 3) in float aTexIndex; \n"
			"out vec4 ourColor; \n"
			"out vec2 TexCoord; \n"
			"out float TexIndex; \n"
			"uniform mat4 sViewProjectionMatrix;"
			"void main()\n"
			"{\n"
			"	gl_Position = sViewProjectionMatrix * vec4(aPos, 1.0); \n"
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

		 data.imGuiRenderer->Init(window);

		 data.batchdata.vertsStart = new Vertex[data.batchdata.MaxVertices];
		 data.batchdata.indicesStart = new unsigned int[data.batchdata.MaxIndices];

		 unsigned int whiteTextureData = 0xffffffff;
		 std::shared_ptr<Texture> whiteTexture = std::make_shared<Texture>(1, 1, &whiteTextureData);
		 data.texLib.AddTexture(whiteTexture, "whiteTexture");
		 data.batchdata.textures[0] = "whiteTexture";

		 if (data.usingFrameBuffer)
		 {
			 unsigned int windowWidth = Input::GetWindowWidth();
			 unsigned int windowHeight = Input::GetWindowHeight();
			 data.framebufferSize = { windowWidth, windowHeight };
		 }
	}

	void Renderer::Shutdown()
	{
		delete[] data.batchdata.vertsStart;
		delete[] data.batchdata.indicesStart;
		data.imGuiRenderer->Shutdown();

		if (data.usingFrameBuffer)
		{
			glDeleteFramebuffers(1, &data.frameBufferRendererID);
			glDeleteTextures(1, &data.colorAttachmentRendererID);
			glDeleteTextures(1, &data.depthAttactmentRendererID);
		}
	}

	void Renderer::startRendererCall()
	{
		if (data.updateQueueFrameBuffer)
		{
			glDeleteFramebuffers(1, &data.frameBufferRendererID);
			glDeleteTextures(1, &data.colorAttachmentRendererID);
			glDeleteTextures(1, &data.depthAttactmentRendererID);
			createFrameBuffer(data.framebufferSize);
			data.orthoCameraController->setWindowSize(data.framebufferSize);

			data.updateQueueFrameBuffer = false;
		}


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (data.usingFrameBuffer)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, data.frameBufferRendererID);

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}
		else
		{
			int windowWidth = Input::GetWindowWidth();
			int windowHeight = Input::GetWindowHeight();
			glViewport(0, 0, windowWidth, windowHeight);
		}

		if (data.isCameraController)
		{
			data.TextureShader.setMat4("sViewProjectionMatrix", data.orthoCameraController->getViewProjectionMatrix());
		}
		else
		{
			data.TextureShader.setMat4("sViewProjectionMatrix", glm::mat4(1.0f));
		}

		data.TextureShader.Use();
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
		if (data.usingFrameBuffer)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}


	void Renderer::endImguiRendererCall()
	{
		data.imGuiRenderer->EndRendererCall();
	}

	unsigned int Renderer::getColorAttachment()
	{
		return data.colorAttachmentRendererID;
	}

	//Drawing backdrops 
	void Renderer::DrawBackDrop(const glm::vec3 color)
	{
		Renderer::DrawBackDrop(glm::vec4(color.x, color.y, color.z, 1.0f));
	}

	//TODO: fix DrawBackDrop with the proper dimensions and with use of the orthographic camera controller
	void Renderer::DrawBackDrop(const glm::vec4 color)
	{
		Draw2DQuad(glm::vec2(-5.0f, -5.0f), glm::vec2(10.0f, 10.0f), color);
	}

	void Renderer::DrawBackDrop(const std::string& texSource)
	{
		Draw2DQuad(glm::vec2(-5.0f, -5.0f), glm::vec2(10.0f, 10.0f), texSource);
	}


	//Drawing flat color quads
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

	
	//Drawing Textured Quads
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


	//Drawing flat colored Quads with transform matrix
	void Renderer::Draw2DQuad(const glm::mat4& transform, const glm::vec4& color /*= glm::vec4(1.0f)*/)
	{
		glm::vec4 vertices[4] =
		{
			{ -0.5f, -0.5f, 0.0f, 1.0f },
			{ 0.5f, -0.5f, 0.0f, 1.0f },
			{ 0.5f, 0.5f, 0.0f, 1.0f },
			{ -0.5f,  0.5f, 0.0f, 1.0f }
		};
		
		float textureIndex = 0.0f;

		data.batchdata.vertsPtr->position = transform * vertices[0];
		data.batchdata.vertsPtr->color = color;
		data.batchdata.vertsPtr->texCoords = { 1.0f, 0.0f };
		data.batchdata.vertsPtr->texIndex = textureIndex;
		data.batchdata.vertsPtr++;

		data.batchdata.vertsPtr->position = transform * vertices[1];
		data.batchdata.vertsPtr->color = color;
		data.batchdata.vertsPtr->texCoords = { 1.0f, 1.0f };
		data.batchdata.vertsPtr->texIndex = textureIndex;
		data.batchdata.vertsPtr++;

		data.batchdata.vertsPtr->position = transform * vertices[2];
		data.batchdata.vertsPtr->color = color;
		data.batchdata.vertsPtr->texCoords = { 0.0f, 1.0f };
		data.batchdata.vertsPtr->texIndex = textureIndex;
		data.batchdata.vertsPtr++;

		data.batchdata.vertsPtr->position = transform * vertices[3];
		data.batchdata.vertsPtr->color = color;
		data.batchdata.vertsPtr->texCoords = { 0.0f, 0.0f };
		data.batchdata.vertsPtr->texIndex = textureIndex;
		data.batchdata.vertsPtr++;
		data.batchdata.QuadCount++;
	}

	void Renderer::Draw2DQuad(const glm::mat4& transform, const glm::vec3& color)
	{
		Draw2DQuad(transform, glm::vec4(color.x, color.y, color.z, 1.0f));
	}


	//Drawing textured quads with transform matrix
	void Renderer::Draw2DQuad(const glm::mat4& transform, const std::string& texName, const glm::vec4& color /*= glm::vec4(1.0f)*/)
	{
		glm::vec4 vertices[4] =
		{
			{ -0.5f, -0.5f, 0.0f, 1.0f },
			{ 0.5f, -0.5f, 0.0f, 1.0f },
			{ 0.5f, 0.5f, 0.0f, 1.0f },
			{ -0.5f,  0.5f, 0.0f, 1.0f }
		};

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

		data.batchdata.vertsPtr->position = transform * vertices[0];
		data.batchdata.vertsPtr->color = color;
		data.batchdata.vertsPtr->texCoords = { 1.0f, 0.0f };
		data.batchdata.vertsPtr->texIndex = textureIndex;
		data.batchdata.vertsPtr++;

		data.batchdata.vertsPtr->position = transform * vertices[1];
		data.batchdata.vertsPtr->color = color;
		data.batchdata.vertsPtr->texCoords = { 1.0f, 1.0f };
		data.batchdata.vertsPtr->texIndex = textureIndex;
		data.batchdata.vertsPtr++;

		data.batchdata.vertsPtr->position = transform * vertices[2];
		data.batchdata.vertsPtr->color = color;
		data.batchdata.vertsPtr->texCoords = { 0.0f, 1.0f };
		data.batchdata.vertsPtr->texIndex = textureIndex;
		data.batchdata.vertsPtr++;

		data.batchdata.vertsPtr->position = transform * vertices[3];
		data.batchdata.vertsPtr->color = color;
		data.batchdata.vertsPtr->texCoords = { 0.0f, 0.0f };
		data.batchdata.vertsPtr->texIndex = textureIndex;
		data.batchdata.vertsPtr++;
		data.batchdata.QuadCount++;
	}

	void Renderer::Draw2DQuad(const glm::mat4& transform, const std::string& texName, const glm::vec3& color)
	{
		Draw2DQuad(transform, texName, glm::vec4(color.x, color.y, color.z, 1.0f));
	}


	//Drawing rotated quads with flat colors
	void Renderer::Draw2DRotatedQuad(const glm::vec2& corner, const glm::vec2& size, float rotation, glm::vec4 color /*= glm::vec4(1.0f)*/)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(corner.x, corner.y, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		Draw2DQuad(transform, color);
	}

	void Renderer::Draw2DRotatedQuad(const glm::vec2& corner, const glm::vec2& size, float rotation, glm::vec3 color)
	{
		Draw2DRotatedQuad(corner, size, rotation, glm::vec4( color.x, color.y, color.z, 1.0f ));
	}


	//Drawing rotated quads with textures
	void Renderer::Draw2DRotatedQuad(const glm::vec2& corner, const glm::vec2& size, float rotation, const std::string& texName, glm::vec4 color /*= glm::vec4(1.0f)*/)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(corner.x, corner.y, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		Draw2DQuad(transform, texName, color);
	}

	void Renderer::Draw2DRotatedQuad(const glm::vec2& corner, const glm::vec2& size, float rotation, const std::string& texSource, glm::vec3 color)
	{
		Draw2DRotatedQuad(corner, size, rotation, texSource, glm::vec4(color.x, color.y, color.z, 1.0f));
	}


	//Adding textures to tex lib
	void Renderer::AddTexture(const std::string& texSource, bool alpha, const std::string& name)
	{
		data.texLib.AddTexture(texSource, alpha, name);
	}


	//Camera controller
	void Renderer::AddOrthoCameraController()
	{
		if (!data.isCameraController)
		{
			data.isCameraController = true;

			data.orthoCameraController = std::make_shared<OrthoCameraController>();
		}
	}


	//Adding and drawing sprites with spritesheets
	void Renderer::AddSpritesheet(const std::string& texSource, bool alpha, const std::string& name, const glm::vec2& spriteSize)
	{
		data.texLib.AddTexture(texSource, alpha, name);
		std::shared_ptr<Spritesheet> spritesheet = std::make_shared<Spritesheet>(spriteSize);
		data.spritesheets[name] = spritesheet;
	}

	void Renderer::DrawSprite(const glm::vec2& corner, const glm::vec2& size, std::string spritesheetName,
		const glm::vec2& spriteCoords, const glm::vec2& spriteSize, glm::vec4 color)
	{
		float textureIndex = 1.0f;
		bool uniqueTexture = true;
		for (int i = 1; i < data.batchdata.texIndex; i++)
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
		}

		unsigned int spritesheetWidth = data.texLib.LoadTexture(spritesheetName)->getWidth();
		unsigned int spritesheetHeight = data.texLib.LoadTexture(spritesheetName)->getHeight();
		std::shared_ptr<Spritesheet> spritesheet = data.spritesheets[spritesheetName];
		glm::vec2 texCoords[] = {
			{ (spriteCoords.x + spriteSize.x) * spritesheet->spriteSize.x / spritesheetWidth, spriteCoords.y * spritesheet->spriteSize.y / spritesheetHeight },
			{ (spriteCoords.x + spriteSize.x) * spritesheet->spriteSize.x / spritesheetWidth, (spriteCoords.y + spriteSize.y) * spritesheet->spriteSize.y / spritesheetHeight },
			{ (spriteCoords.x) * spritesheet->spriteSize.x / spritesheetWidth, (spriteCoords.y + spriteSize.y) * spritesheet->spriteSize.y / spritesheetHeight },
			{ (spriteCoords.x) * spritesheet->spriteSize.x / spritesheetWidth, spriteCoords.y * spritesheet->spriteSize.y / spritesheetHeight }
		};

		data.batchdata.vertsPtr->position = { corner.x + size.x, corner.y, 0.0f };
		data.batchdata.vertsPtr->color = color;
		data.batchdata.vertsPtr->texCoords = texCoords[0];
		data.batchdata.vertsPtr->texIndex = textureIndex;
		data.batchdata.vertsPtr++;

		data.batchdata.vertsPtr->position = { corner.x + size.x, corner.y + size.y, 0.0f };
		data.batchdata.vertsPtr->color = color;
		data.batchdata.vertsPtr->texCoords = texCoords[1];
		data.batchdata.vertsPtr->texIndex = textureIndex;
		data.batchdata.vertsPtr++;

		data.batchdata.vertsPtr->position = { corner.x, corner.y + size.y, 0.0f };
		data.batchdata.vertsPtr->color = color;
		data.batchdata.vertsPtr->texCoords = texCoords[2];
		data.batchdata.vertsPtr->texIndex = textureIndex;
		data.batchdata.vertsPtr++;

		data.batchdata.vertsPtr->position = { corner.x, corner.y, 0.0f };
		data.batchdata.vertsPtr->color = color;
		data.batchdata.vertsPtr->texCoords = texCoords[3];
		data.batchdata.vertsPtr->texIndex = textureIndex;
		data.batchdata.vertsPtr++;
		data.batchdata.QuadCount++;
	}

	void Renderer::DrawSprite(const glm::vec2& corner, const glm::vec2& size, std::string spritesheetName,
		const glm::vec2& spriteCoords, const glm::vec2& spriteSize, glm::vec3 color)
	{
		DrawSprite(corner, size, spritesheetName, spriteCoords, spriteSize, glm::vec4(color.x, color.y, color.z, 1.0f));
	}

	//Rendering all the quads in the batch
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
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, data.batchdata.QuadCount * 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		GLuint buffers[] = { VBO, EBO };
		glDeleteBuffers(2, buffers);
		unsigned int vertexArraysBuffer[] = {VAO};
		glDeleteVertexArrays(1, vertexArraysBuffer);
	}


	void Renderer::createFrameBuffer(glm::vec2 size)
	{
		glViewport(0, 0, size.x, size.y);
		glGenFramebuffers(1, &data.frameBufferRendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, data.frameBufferRendererID);

		glGenTextures(1, &data.colorAttachmentRendererID);
		glBindTexture(GL_TEXTURE_2D, data.colorAttachmentRendererID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, data.colorAttachmentRendererID, 0);

		glCreateTextures(GL_TEXTURE_2D, 1, &data.depthAttactmentRendererID);
		glBindTexture(GL_TEXTURE_2D, data.depthAttactmentRendererID);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, size.x, size.y);
		// glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height, 0,
		// 	GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, data.depthAttactmentRendererID, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			Logger::error("Framebuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Renderer::updateFramebuffer(glm::vec2 size)
	{
		data.updateQueueFrameBuffer = true;
		data.framebufferSize = size;
	}

	//Updating every frame
	void Renderer::OnUpdate(TimeStep ts)
	{
		if (data.isCameraController)
		{
			data.orthoCameraController->OnUpdate(ts);
		}
	}

	//Called every time an event is called
	void Renderer::OnEvent(Event& e)
	{
		if (data.isCameraController)
		{
			data.orthoCameraController->OnEvent(e);
		}
	}

	void Renderer::OnWindowResize(WindowResizeEvent& e)
	{
		//if (!data.usingFrameBuffer)
		//{
		//data.orthoCameraController->setWindowSize(glm::vec2((float)e.width, (float)e.height));
		//}
	}

}