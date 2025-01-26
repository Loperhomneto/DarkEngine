#include "dkpch.h"
#include "TextureLibrary.h"

namespace Dark
{

	TextureLibrary::TextureLibrary()
	{
		m_textures = std::unordered_map < std::string, std::shared_ptr<Texture>>();
	}

	void TextureLibrary::AddTexture(std::string texSource, bool alpha, std::string name)
	{
		std::shared_ptr<Texture> texture = std::make_shared<Texture>(texSource, alpha);

		m_textures[name] = texture;
	}

	void TextureLibrary::AddTexture(const std::shared_ptr<Texture>& texture, std::string name)
	{
		m_textures[name] = texture;
	}

	void TextureLibrary::AddTexture(unsigned int width, unsigned int height, void* data, std::string name)
	{
		std::shared_ptr<Texture> texture = std::make_shared<Texture>(width, height, data);

		m_textures[name] = texture;
	}

	std::shared_ptr<Texture> TextureLibrary::LoadTexture(std::string name)
	{
		return m_textures[name];
	}

	// Spritesheets
	SpritesheetLibrary::SpritesheetLibrary()
	{
		m_spritesheets = std::unordered_map < std::string, std::shared_ptr<SpriteSheet>>();
	}

	void SpritesheetLibrary::AddSpritesheet(std::string texSource, bool alpha, std::string name, unsigned int width, unsigned int height)
	{
		std::shared_ptr<Texture> texture = std::make_shared<Texture>(texSource, alpha);
		std::shared_ptr<SpriteSheet> spritesheet = std::make_shared<SpriteSheet>(texture, width, height);

		m_spritesheets[name] = spritesheet;
	}
	void SpritesheetLibrary::AddSpritesheet(const std::shared_ptr<Texture>& texture, std::string name, unsigned int width, unsigned int height)
	{
		std::shared_ptr<SpriteSheet> spritesheet = std::make_shared<SpriteSheet>(texture, width, height);
		m_spritesheets[name] = spritesheet;
	}
	void SpritesheetLibrary::AddSpritesheet(unsigned int width, unsigned int height, void* data, std::string name)
	{
		std::shared_ptr<Texture> texture = std::make_shared<Texture>(width, height, data);
		std::shared_ptr<SpriteSheet> spritesheet = std::make_shared<SpriteSheet>(texture, width, height);

		m_spritesheets[name] = spritesheet;
	}
	std::shared_ptr<SpriteSheet> SpritesheetLibrary::LoadSpritesheet(std::string name)
	{
		return m_spritesheets[name];
	}

}
