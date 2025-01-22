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

	std::shared_ptr<Texture> TextureLibrary::LoadTexture(std::string name)
	{
		return m_textures[name];
	}

}


