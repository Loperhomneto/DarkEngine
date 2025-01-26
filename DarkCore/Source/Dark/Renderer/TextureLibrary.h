#pragma once
#include "dkpch.h"
#include "Texture.h"
#include "Dark/Core.h"

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

	struct SpriteSheet
	{
		std::shared_ptr<Texture> texture;
		int spritesheetWidth;
		int spritesheetHeight;
	};

	class SpritesheetLibrary
	{
	public:
		SpritesheetLibrary();

		void AddSpritesheet(std::string texSource, bool alpha, std::string name, unsigned int width, unsigned int height);
		void AddSpritesheet(const std::shared_ptr<Texture>& texture, std::string name, unsigned int width, unsigned int height);
		void AddSpritesheet(unsigned int width, unsigned int height, void* data, std::string name);
		std::shared_ptr<SpriteSheet> LoadSpritesheet(std::string name);
	private:
		std::unordered_map<std::string, std::shared_ptr<SpriteSheet>> m_spritesheets;
	};

}



