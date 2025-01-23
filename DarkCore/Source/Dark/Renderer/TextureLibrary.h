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
		void AddTexture(std::shared_ptr<Texture> texture, std::string name);
		std::shared_ptr<Texture> LoadTexture(std::string name);
	private:
		std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
	};

}



