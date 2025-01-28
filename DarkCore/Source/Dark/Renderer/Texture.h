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
		unsigned int getWidth() { return m_width;  }
		unsigned int getHeight() { return m_height;  }
	private:
		unsigned int m_texture;
		unsigned int m_width;
		unsigned int m_height;
	};
}

