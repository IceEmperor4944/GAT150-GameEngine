#pragma once
#include "Components/Component.h"

class CharacterComponent : public Component {
public:
	CLASS_DECLARATION(CharacterComponent)
	CLASS_PROTOTYPE(CharacterComponent)

	void Initialize() override;
	void Update(float dt) override;

	void OnCollisionEnter(Actor* actor);
	void OnCollisionExit(Actor* actor);
public:
	int groundCount = 0;
	float speed = 0.0f;

	int wallCount = 0;
	float jumpHeight = 0.0f;
	float jumpTimer = 0.0f;

	bool hit = false;
	float deathTimer = 100.0f;

	float dashMod = 0.0f;
	int dashDuration = 0;
	int dashCountdown = 0;
	bool hasDashed = false;
	bool isDash = false;

	class PhysicsComponent* physics{ nullptr };
	class TextureAnimationComponent* animation{ nullptr };
};