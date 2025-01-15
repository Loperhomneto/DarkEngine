#pragma once

#include "Texture.h"
#include <memory>
#include <unordered_map>

namespace Dark
{

	class TextureLibrary
	{
	public:
		TextureLibrary();

		void AddTexture(std::string texSource, bool alpha, std::string name);
		std::shared_ptr<Texture> LoadTexture(std::string name);
	private:
		std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
	};

}



