#pragma once
#include <unordered_map>
#include <string>
#include <memory>

namespace irrklang
{
	struct ISoundEngine;
}

namespace Dark
{

	class Deconstructor
	{
	public:
		~Deconstructor();
	};

	class SoundEngine
	{
	public:
		static void AddSound(std::string source, std::string sound);
		static void PlaySound(std::string name, float volume);
	private:
		static std::unordered_map<std::string, std::string> m_sounds;
		static irrklang::ISoundEngine* engine;
		static Deconstructor deconstructor;
		
		static void Drop();

		friend class Deconstructor;
	};

}