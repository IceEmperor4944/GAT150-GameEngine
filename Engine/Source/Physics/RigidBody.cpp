#include "RigidBody.h"
#include "Physics.h"

RigidBody::RigidBody(const Transform& transform, const Vector2& size, const def_t& def, const Physics& physics)
{
	b2BodyDef bodyDef = b2DefaultBodyDef();

	// set body definition
	bodyDef.type = (def.isDynamic) ? b2_dynamicBody : b2_staticBody;
	bodyDef.position = ConvertVec2(Physics::ScreenToWorld(transform.position));
	bodyDef.rotation = b2MakeRot(Math::DegToRad(transform.rotation));
	bodyDef.fixedRotation = def.constrainAngle;
	bodyDef.gravityScale = def.gravityScale;
	bodyDef.linearDamping = def.damping;
	bodyDef.angularDamping = def.angularDamping;
	bodyDef.userData = def.actor;

	// create body
	m_bodyId = b2CreateBody(physics.m_worldId, &bodyDef);

	// set shape
	b2Vec2 bsize = ConvertVec2(Physics::ScreenToWorld(size));
	b2Polygon box = b2MakeBox(bsize.x, bsize.y);
	b2ShapeDef shapeDef = b2DefaultShapeDef();
	shapeDef.friction = def.restitution;
	shapeDef.restitution = def.restitution;
	shapeDef.density = def.density;
	shapeDef.isSensor = def.isSensor;

	b2CreatePolygonShape(m_bodyId, &shapeDef, &box);
}

RigidBody::~RigidBody()
{
	b2DestroyBody(m_bodyId);
}

void RigidBody::SetTransform(const Vector2& position, float rotation)
{
	b2Body_SetTransform(m_bodyId, ConvertVec2(Physics::ScreenToWorld(position)), b2MakeRot(Math::DegToRad(rotation)));
}

Vector2 RigidBody::GetPosition()
{
	return Physics::WorldToScreen(ConvertVec2(b2Body_GetPosition(m_bodyId)));
}

float RigidBody::GetAngle()
{
	return Math::RadToDeg(b2Rot_GetAngle(b2Body_GetRotation(m_bodyId)));
}

void RigidBody::ApplyForce(const Vector2& force)
{
	b2Body_ApplyForceToCenter(m_bodyId, ConvertVec2(Physics::ScreenToWorld(force)), true);
}

void RigidBody::SetVelocity(const Vector2& velocity)
{
	b2Body_SetLinearVelocity(m_bodyId, ConvertVec2(Physics::ScreenToWorld(velocity)));
}

Vector2 RigidBody::GetVelocity()
{
	return Physics::WorldToScreen(ConvertVec2(b2Body_GetLinearVelocity(m_bodyId)));
}

void RigidBody::ApplyTorque(float torque)
{
	b2Body_ApplyTorque(m_bodyId, torque, true);
}

void RigidBody::SetAngularVelocity(float velocity)
{
	b2Body_SetAngularVelocity(m_bodyId, velocity);
}
