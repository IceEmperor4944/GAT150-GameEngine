#pragma once

//CORE
#include "Core/EAssert.h"
#include "Core/EFile.h"
#include "Core/ETime.h"
#include "Core/Json.h"
#include "Core/Singleton.h"
#include "Core/Factory.h"

//SYSTEMS
//RENDERER
#include "Renderer/Renderer.h"
#include "Renderer/Particle.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Renderer/Model.h"
#include "Renderer/Texture.h"

//INPUT
#include "Input/Input.h"

//AUDIO
#include "Audio/Audio.h"

//MATH
#include "Math/Vector2.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"

//FRAMEWORK
#include "Framework/Actor.h"
#include "Framework/Scene.h"

//RESOURCES
#include "Resources/Resource.h"
#include "Resources/ResourceManager.h"

//COMPONENTS
#include "Components/TextureComponent.h"

#include <fmod.hpp>
#include <SDL.h>
#include <memory>
#include <cassert>

class Engine {
public:
	Engine() = default;
	~Engine() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	Renderer& GetRenderer() { return *m_renderer; }
	Input& GetInput() { return *m_input; }
	Audio& GetAudio() { return *m_audio; }
	ParticleSystem& GetPS() { return *m_particleSystem; }

	Time& GetTime() { return *m_time; }

	bool IsQuit() { return quit; }
private:
	bool quit = false;

	std::unique_ptr<Time> m_time;

	std::unique_ptr<Renderer> m_renderer;
	std::unique_ptr<Input> m_input;
	std::unique_ptr<Audio> m_audio;

	std::unique_ptr<ParticleSystem> m_particleSystem;
};