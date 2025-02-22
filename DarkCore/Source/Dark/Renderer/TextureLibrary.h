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

		void AddTexture(std::string texName, bool alpha, std::string name);
		void AddTexture(const std::shared_ptr<Texture>& texture, std::string name);
		void AddTexture(unsigned int width, unsigned int height, void* data, std::string name);
		std::shared_ptr<Texture> LoadTexture(std::string name);
	private:
		std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
	};

}



