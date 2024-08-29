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
	//MOVEMENT
	//walk
	Vector2 direction{ 0, 0 };
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) direction.x = -1.0f;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) direction.x = 1.0f;	
	
	//jump
	float modifier = (groundCount) ? 1 : 0.5f;
	physics->ApplyForce(direction * speed * modifier);

	if (groundCount && !wallCount && owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_Z) && !owner->scene->engine->GetInput().GetPrevKeyDown(SDL_SCANCODE_Z)) {
		physics->SetVelocity(Vector2{ 0.0f, -jumpHeight });
	}

	//wall jump
	if (wallCount && jumpTimer <= 0.0f && !groundCount && owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_Z) && !owner->scene->engine->GetInput().GetPrevKeyDown(SDL_SCANCODE_Z)) {
		physics->SetVelocity(Vector2{ direction.x * speed * modifier * -0.1f, -jumpHeight });
		jumpTimer = 20.0f;
	}

	//dash
	dashDuration = (dashDuration - 1 < 0) ? dashDuration - 1 : 0;
	dashCountdown = (dashCountdown - 1 < 0) ? dashCountdown - 1 : 0;

	if (dashDuration > 0) direction.y = 0;
	else if (wallCount) direction.y = (direction.y + dt < 2) ? direction.y + dt : 2.0f;
	else direction.y += dt;

	float vel;

	switch (dashDuration) {
	case 5: {
		vel = -dashMod * speed * 0.5f;
		physics->SetVelocity({ vel, vel });
	}
		break;
	case 3: {
		vel = -dashMod * speed * 0.5f;
		physics->SetVelocity({ vel, vel });
	}
		break;
	case 2:
	{
		vel = -dashMod * speed;
		physics->SetVelocity({ vel, vel });
	}
		break;
	case 1: {
		vel = -dashMod * speed * 2.0f;
		physics->SetVelocity({ vel, vel });
	}
		break;
	}

	if ((wallCount || groundCount) && (!hasDashed && owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_X))) {
		dashDuration = 100;
		physics->SetVelocity(direction * speed * dashMod);
		hasDashed = true;
		dashCountdown = 50;
		isDash = true;
	}

	if (dashCountdown <= 0 && (groundCount || wallCount)) {
		hasDashed = false;
	}

	if (wallCount) {
		hasDashed = false;
	}

	//ANIMATION
	if (physics->velocity.x < -0.1f) animation->hflip = true;
	else if (physics->velocity.x > 0.1f) animation->hflip = false;

	if (hit) {
		animation->SetAnimation("death");
		deathTimer--;
	}
	else if (Math::Abs(physics->velocity.x) > 0.1f) animation->SetAnimation("walk");
	else if (!groundCount && !wallCount) animation->SetAnimation("jump");
	else if (wallCount && !groundCount) animation->SetAnimation("slide");
	//else if (isDash) animation->SetAnimation("dash");
	else animation->SetAnimation("idle");

	if(deathTimer <= 0)	owner->destroyed = true;

	jumpTimer--;
}

void CharacterComponent::OnCollisionEnter(Actor* actor) {
	//std::cout << "player hit\n";
	//EVENT_NOTIFY(PlayerDead);
	for (auto tag : actor->tag) {
		if (tag == "Ground") {
			groundCount++;
			jumpTimer = 0.0f;
		}
		if (tag == "Wall") wallCount++;
		//isDash = false;
		if (tag == "Fire" || tag == "Enemy") hit = true;
	}
}

void CharacterComponent::OnCollisionExit(Actor* actor) {
	for (auto tag : actor->tag) {
		if (tag == "Ground") groundCount--;
		if (tag == "Wall") wallCount--;
	}
}

void CharacterComponent::Read(const json_t& value) {
	READ_DATA(value, speed);
	READ_DATA(value, jumpHeight);
	//READ_DATA(value, dashMod);
}

void CharacterComponent::Write(json_t& value) {
	//
}