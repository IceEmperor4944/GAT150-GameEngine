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
	float jumpHeight = 0.0f;

	class PhysicsComponent* physics{ nullptr };
	class TextureAnimationComponent* animation{ nullptr };
};