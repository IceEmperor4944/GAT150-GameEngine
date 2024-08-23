#pragma once
#include "Resources/Resource.h"
#include <fmod.hpp>

class AudioClip : public Resource {
public:
	AudioClip() = default;
	~AudioClip();
	bool Create(std::string name, ...) override;
	bool Load(const std::string& filename, class Audio& audio);
	
	friend class Audio;
	friend class AudioSource;
private:
	FMOD::Sound * m_sound{ nullptr };
};