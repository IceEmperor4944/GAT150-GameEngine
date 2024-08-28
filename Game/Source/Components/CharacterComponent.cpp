#include "CharacterComponent.h"
#include "Engine.h"

FACTORY_REGISTER(CharacterComponent)

void CharacterComponent::Initialize() {
	owner->OnCollisionEnter = std::bind(&CharacterComponent::OnCollisionEnter, this, std::placeholders::_1);
	owner->OnCollisionExit = std::bind(&CharacterComponent::OnCollisionExit, this, std::placeholders::_1);

	physics = owner->GetComponent<PhysicsComponent>();
	animation = owner->GetComponent<TextureAnimationComponent>();
}

void CharacterComponent::Update(float dt) {
	Vector2 direction{ 0, 0 };	
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;	
	
	float modifier = (groundCount) ? 1 : 0.5f;
	physics->ApplyForce(direction * speed * modifier);

	if (groundCount && owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
		physics->SetVelocity(Vector2{ 0.0f, -jumpHeight });
	}

	if (physics->velocity.x < -0.1f) animation->hflip = true;
	else if (physics->velocity.x > 0.1f) animation->hflip = false;

	if (Math::Abs(physics->velocity.x) > 0.1f) animation->SetAnimation("walk");
	else animation->SetAnimation("idle");
}

void CharacterComponent::OnCollisionEnter(Actor* actor) {
	//std::cout << "player hit\n";
	//EVENT_NOTIFY(PlayerDead);
	if (actor->tag == "Ground") groundCount++;
}

void CharacterComponent::OnCollisionExit(Actor* actor) {
	if (actor->tag == "Ground") groundCount--;
}

void CharacterComponent::Read(const json_t& value) {
	READ_DATA(value, speed);
	READ_DATA(value, jumpHeight);
}

void CharacterComponent::Write(json_t& value) {
	//
}