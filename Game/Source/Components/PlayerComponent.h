#pragma once
#include "Components/Component.h"

class PlayerComponent : public Component {
public:
	CLASS_DECLARATION(PlayerComponent)

	void Initialize() override;
	void Update(float dt) override;

	void OnCollisionEnter(Actor* actor);
public:
	float speed = 0.0f;
};