#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Components/Component.h"

#include <string>
#include <memory>
#include <vector>
#include <functional>

class Scene; //forward declaration - makes it so there isnt looping of includes
class Renderer; //can also put class/struct in front of usage if only one

class Actor : public Object {
public:
	Actor() = default;
	Actor(const Transform& transform) : transform{ transform } {}
	Actor(const Actor& other);

	CLASS_DECLARATION(Actor)
	CLASS_PROTOTYPE(Actor)

	void Initialize() override;
	virtual void Update(float dt);
	virtual void Draw(Renderer& renderer);

	std::function<void(Actor*)> OnCollisionEnter;

	void AddComponent(std::unique_ptr<Component> component);

	template<typename T>
	T* GetComponent();
	template<typename T>
	std::vector<T*> GetComponents();

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

template<typename T>
T* Actor::GetComponent() {
	for (auto& component : components) {
		T* result = dynamic_cast<T*>(component.get());
		if (result) return result;
	}

	return nullptr;
}

template<typename T>
inline std::vector<T*> Actor::GetComponents() {
	std::vector<T*> results;

	for (auto& component : components) {
		T* result = dynamic_cast<T*>(component.get());
		if (result) results.push_back(result);
	}

	return results;
}