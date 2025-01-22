#include "dkpch.h"
#include "Soundengine.h"
#include "irrKlang.h"

namespace Dark 
{
	irrklang::ISoundEngine* SoundEngine::engine = irrklang::createIrrKlangDevice();
	std::unordered_map<std::string, std::string> SoundEngine::m_sounds = 
		std::unordered_map<std::string, std::string>();
	Deconstructor SoundEngine::deconstructor = Deconstructor();

	void SoundEngine::AddSound(std::string source, std::string sound)
	{
		m_sounds[sound] = source;
	}

	void SoundEngine::PlaySound(std::string name, float volume)
	{
		engine->setSoundVolume(volume);
		engine->play2D(m_sounds[name].c_str());

	}

	void SoundEngine::Drop()
	{
		engine->drop();
	}

	Deconstructor::~Deconstructor()
	{
		SoundEngine::Drop();
	}
}