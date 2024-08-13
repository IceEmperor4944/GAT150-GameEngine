#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Components/Component.h"

#include <string>
#include <memory>
#include <vector>

class Scene; //forward declaration - makes it so there isnt looping of includes
class Renderer; //can also put class/struct in front of usage if only one

class Actor : public Object {
public:
	Actor() = default;
	Actor(const Transform& transform) : transform{ transform } {}

	CLASS_DECLARATION(Actor)

	void Initialize() override;
	virtual void Update(float dt);
	virtual void Draw(Renderer& renderer);

	void AddComponent(std::unique_ptr<Component> component);

	friend class Scene;
public:
	std::string tag;
	float lifespan = 0;
	bool destroyed = false;
	
	Transform transform{ {0, 0}, 0, 1 };
	Scene* scene{ nullptr };
protected:
	std::vector<std::unique_ptr<Component>> components;
};