#include "CircleCollisionComponent.h"
#include "Framework/Actor.h"

FACTORY_REGISTER(CircleCollisionComponent)

void CircleCollisionComponent::Initialize() {

}

void CircleCollisionComponent::Update(float dt) {

}

bool CircleCollisionComponent::CheckCollision(const CollisionComponent* collision) {
    //distance <= radii
    float r1 = radius;
    float r2 = (dynamic_cast<const CircleCollisionComponent*>(collision))->radius;
    //distance = collision1 <-> collision2
    float distance = owner->transform.position.Distance(collision->owner->transform.position);
    
    return (distance <= (r1 + r2));
}

void CircleCollisionComponent::Read(const json_t& value) {
    READ_DATA(value, radius);
}

void CircleCollisionComponent::Write(json_t& value) {
    //
}