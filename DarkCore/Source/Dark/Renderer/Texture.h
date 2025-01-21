#pragma once
#include "Dark/Core.h"

namespace Dark
{
	class Texture
	{
	public:
		Texture(std::string source, bool alpha);
	
		void Bind(int unit);

		unsigned int getID() { return m_texture; }
	private:
		std::string source;
		bool alpha;
		unsigned int m_texture;
	};
}

