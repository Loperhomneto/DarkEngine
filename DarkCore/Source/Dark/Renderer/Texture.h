#pragma once
#include <string>

namespace Dark
{
	class Texture
	{
	public:
		Texture(std::string source, bool alpha);
	
		void Create();
		void Bind(int unit);

		unsigned int getID() { return m_texture; }
	private:
		std::string source;
		bool alpha;
		unsigned int m_texture;
	};
}

