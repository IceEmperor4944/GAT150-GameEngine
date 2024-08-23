#pragma once
#include <fmod.hpp>
#include <map>
#include <string>

class Audio {
public:
	Audio() = default;
	~Audio() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	bool AddSound(const std::string& name);
	bool PlaySound(const std::string& name);

	friend class AudioClip;
	friend class AudioSource;
private:
	FMOD::System* m_audio{ nullptr };
	std::map<std::string, FMOD::Sound*> m_sounds;
};