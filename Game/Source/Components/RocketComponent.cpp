#include "RocketComponent.h"
#include "Engine.h"

FACTORY_REGISTER(RocketComponent)

void RocketComponent::Initialize() {
	owner->OnCollisionEnter = std::bind(&RocketComponent::OnCollisionEnter, this, std::placeholders::_1);
}

void RocketComponent::Update(float dt) {
	owner->GetComponent<PhysicsComponent>()->SetVelocity(owner->transform.Forward() * speed); ///can read in a speed variable later, then use that instead of set value
}

void RocketComponent::OnCollisionEnter(Actor* actor) {
	if (!actor->destroyed && (actor->name == "enemy")) {
		EVENT_NOTIFY_DATA(AddPoints, 200);
		actor->destroyed = true;
	}
}

void RocketComponent::Read(const json_t& value) {
	READ_DATA(value, speed);
}

void RocketComponent::Write(json_t& value) {
	//
}