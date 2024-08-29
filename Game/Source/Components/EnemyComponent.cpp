#include "EnemyComponent.h"
#include "Engine.h"

FACTORY_REGISTER(EnemyComponent)

void EnemyComponent::Initialize() {
	owner->OnCollisionEnter = std::bind(&EnemyComponent::OnCollisionEnter, this, std::placeholders::_1);
	owner->OnCollisionExit = std::bind(&EnemyComponent::OnCollisionExit, this, std::placeholders::_1);

	physics = owner->GetComponent<PhysicsComponent>();
	animation = owner->GetComponent<TextureAnimationComponent>();
}

void EnemyComponent::Update(float dt) {
	auto player = owner->scene->GetActor<Actor>("player");
	Vector2 direction = player->transform.position - owner->transform.position;
	physics->SetVelocity(direction * speed);
}

void EnemyComponent::OnCollisionEnter(Actor* actor) {
	//std::cout << "player hit\n";
	//EVENT_NOTIFY(PlayerDead);
}

void EnemyComponent::OnCollisionExit(Actor* actor) {
	//
}

void EnemyComponent::Read(const json_t& value) {
	READ_DATA(value, speed);
	//READ_DATA(value, jumpHeight);
	//READ_DATA(value, dashMod);
}

void EnemyComponent::Write(json_t& value) {
	//
}