#include "PlayerComponent.h"
#include "Engine.h"

void PlayerComponent::Initialize() {

}

void PlayerComponent::Update(float dt) {
	Vector2 direction{ 0, 0 };
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
	owner->GetComponent<PhysicsComponent>()->ApplyForce(direction * speed); ///can read in a speed variable later, then use that instead of set value
}

void PlayerComponent::Read(const json_t& value) {
	READ_DATA(value, speed);
}

void PlayerComponent::Write(json_t& value) {
	//
}