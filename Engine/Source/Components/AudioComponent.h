#pragma once
#include "Component.h"

class AudioComponent : public Component {
public:
	AudioComponent() = default;
	AudioComponent(const AudioComponent& other);
	CLASS_DECLARATION(AudioComponent)
	CLASS_PROTOTYPE(AudioComponent)
	void Initialize() override;
	void Update(float dt) override;
	void Play();
	void Play(bool loop, float volume, float pitch);
	bool IsPlaying();
	void Stop();
	void Pause(bool pause = true);
	void SetVolume(float volume);
	void SetPitch(float pitch);
public:
	bool playOnStart{ false };
	bool loop{ false };
	float volume{ 1 };
	float pitch{ 1 };
	std::string soundName;
private:
	std::unique_ptr<class AudioSource> m_audioSource;
};