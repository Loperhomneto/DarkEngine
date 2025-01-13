#include "Renderer.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

namespace Dark {

	Shader Renderer::Shader1 = Shader();
	Shader Renderer::TextureShader = Shader();
	TextureLibrary Renderer::texLib = TextureLibrary();
	int Renderer::units = 0;
	
	void Renderer::Init()
	{
		const char* vSource1 = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"layout (location = 1) in vec3 aColor;\n"
			"uniform int sHeight;\n"
			"uniform int sWidth;\n"
			"out vec3 ourColor;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(((aPos.x*2)-sWidth)/sWidth, ((aPos.y*2)-sHeight)/sHeight, aPos.z, 1.0);\n"
			"   ourColor = aColor;\n"
			"}\0";
		const char* fSource1 = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"in vec3 ourColor;"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(ourColor, 1.0f);\n"
			"}\n\0";

		const char* vSource2 = "#version 330 core\n"
			"layout(location = 0) in vec3 aPos; \n"
			"layout(location = 1) in vec3 aColor; \n"
			"layout(location = 2) in vec2 aTexCoord; \n"
			"out vec3 ourColor; \n"
			"out vec2 TexCoord; \n"
			"uniform int sHeight;\n"
			"uniform int sWidth;\n"
			"void main()\n"
			"{\n"
			"	gl_Position = vec4(((aPos.x*2)-sWidth)/sWidth, ((aPos.y*2)-sHeight)/sHeight, aPos.z, 1.0); \n"
			"	ourColor = aColor; \n"
			"	TexCoord = aTexCoord; \n"
			"}\0";
		const char* fSource2 = "#version 330 core\n"
			"out vec4 FragColor; \n"
			"in vec3 ourColor; \n"
			"in vec2 TexCoord; \n"
			"uniform sampler2D texture1; \n"
			"void main()\n"
			"{\n"
			"	FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0);\n"
			"}\n\0";

		 Shader1 = Shader(std::string(vSource1), std::string(fSource1));
		 TextureShader = Shader(std::string(vSource2), std::string(fSource2));

		 glEnable(GL_BLEND);
		 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Renderer::startRendererCall(int width, int height)
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		TextureShader.Use();
		TextureShader.setInt("sWidth", width);
		TextureShader.setInt("sHeight", height);

		Shader1.Use();
		Shader1.setInt("sWidth", width);
		Shader1.setInt( "sHeight", height);

		Shader1.Use();
		units = 0;
	}

	Quad Renderer::Draw2DQuad(const glm::vec2& corner, glm::vec2 size, glm::vec3 color)
	{
		float vertices[] = {
			corner.x + size.x, corner.y, 0.0f, color.x, color.y, color.z,  // top right
			corner.x + size.x, corner.y + size.y, 0.0f, color.x, color.y, color.z,  // bottom right
			corner.x, corner.y + size.y, 0.0f, color.x, color.y, color.z,  // bottom left
			corner.x, corner.y, 0.0f, color.x, color.y, color.z   // top left 
		};

		return privateDrawQuad(vertices, sizeof(vertices));
	}

	Quad Renderer::Draw2DQuad(const glm::vec2& corner, glm::vec2 size, std::string texName, glm::vec3 color)
	{
		float vertices[] = {
			corner.x + size.x, corner.y, 0.0f,			color.x, color.y, color.z, 1.0f, 1.0f,// top right
			corner.x + size.x, corner.y + size.y, 0.0f, color.x, color.y, color.z, 1.0f, 0.0f, // bottom right
			corner.x,		   corner.y + size.y, 0.0f,	color.x, color.y, color.z, 0.0f, 0.0f, // bottom left
			corner.x,          corner.y, 0.0f,			color.x, color.y, color.z, 0.0f, 1.0f // top left 
		};

		return privateDrawTexturedQuad(vertices, sizeof(vertices), texName);
	}

	Quad Renderer::Draw2DQuad(const Quad& quad)
	{
		if (quad.texID == 0)
		{
			glBindVertexArray(quad.VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		else
		{
			TextureShader.Use();
			TextureShader.setInt("texture1", units);

			glActiveTexture(GL_TEXTURE0 + units);
			glBindTexture(GL_TEXTURE_2D, quad.texID);
			units++;

			TextureShader.Use();
			glBindVertexArray(quad.VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		return quad;
	}

	Quad Renderer::privateDrawQuad(float* vertices, float length)
	{
		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};

		unsigned int VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, length, vertices, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		Quad quad;
		quad.VAO = VAO;
		return quad;
	}

	Quad Renderer::privateDrawTexturedQuad(float vertices[], float length, std::string texName)
	{

		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		unsigned int VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, length, vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// texture coord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		std::shared_ptr<Texture> texture = texLib.LoadTexture(texName);
		texture->Create();

		TextureShader.Use();
		TextureShader.setInt("texture1", units);

		texture->Bind(units);
		units++;

		TextureShader.Use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		return Quad(VAO, texture->getID());
	}


	void Renderer::AddTexture(std::string texSoure, bool alpha, std::string name)
	{
		texLib.AddTexture(texSoure, alpha, name);
	}

}