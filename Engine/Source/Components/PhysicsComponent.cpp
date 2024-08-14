#include "PhysicsComponent.h"

void PhysicsComponent::Read(const json_t& value) {
	READ_DATA(value, velocity);
	READ_DATA(value, acceleration);
	READ_DATA(value, mass);
	READ_DATA(value, damping);
}

void PhysicsComponent::Write(json_t& value) {

}