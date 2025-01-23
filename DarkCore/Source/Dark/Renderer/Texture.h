#pragma once
#include "Dark/Core.h"

namespace Dark
{
	class Texture
	{
	public:
		Texture(std::string source, bool alpha);
		Texture(unsigned int width, unsigned int height, void* data);
	
		void Bind(int unit);

		unsigned int getID() { return m_texture; }
	private:
		unsigned int m_texture;
	};
}

