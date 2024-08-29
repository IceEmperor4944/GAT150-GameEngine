#pragma once
#include "Components/Component.h"

class EnemyComponent : public Component {
public:
	CLASS_DECLARATION(EnemyComponent)
	CLASS_PROTOTYPE(EnemyComponent)

	void Initialize() override;
	void Update(float dt) override;

	void OnCollisionEnter(Actor* actor);
	void OnCollisionExit(Actor* actor);
public:
	float speed = 0.0f;
	bool hit = false;

	class PhysicsComponent* physics{ nullptr };
	class TextureAnimationComponent* animation{ nullptr };
};