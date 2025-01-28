#pragma once
#include "dkpch.h"
#include "Texture.h"
#include "Dark/Core.h"
#include "glm.hpp"

namespace Dark
{

	class TextureLibrary
	{
	public:
		TextureLibrary();

		void AddTexture(std::string texSource, bool alpha, std::string name);
		void AddTexture(const std::shared_ptr<Texture>& texture, std::string name);
		void AddTexture(unsigned int width, unsigned int height, void* data, std::string name);
		std::shared_ptr<Texture> LoadTexture(std::string name);
	private:
		std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
	};

	//class SpritesheetLibrary
	//{
	//public:
	//	SpritesheetLibrary();

	//	void AddSpritesheet(std::string texSource, bool alpha, std::string name, const glm::vec2& spritesheetSize, const glm::vec2& spriteSize);
	//	void AddSpritesheet(const std::shared_ptr<Texture>& texture, std::string name, const glm::vec2& spritesheetSize, const glm::vec2& spriteSize);
	//	void AddSpritesheet(unsigned int width, unsigned int height, void* data, std::string name, const glm::vec2& spritesheetSize, const glm::vec2& spriteSize);
	//	std::shared_ptr<SpriteSheet> LoadSpritesheet(std::string name);
	//private:
	//	std::unordered_map<std::string, std::shared_ptr<SpriteSheet>> m_spritesheets;
	//};

}



