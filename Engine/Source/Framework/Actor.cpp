#include "Actor.h"
#include "Components/RenderComponent.h"
#include "Core/Factory.h"

void Actor::Initialize() {
	for (auto& component : components) {
		component->Initialize();
	}
}

void Actor::Update(float dt) {
	if (lifespan != 0) {
		lifespan -= dt;
		if (lifespan <= 0) {
			destroyed = true;
		}
	}

	for (auto& component : components) {
		component->Update(dt);
	}

	/*transform.position += (m_velocity * dt);
	m_velocity *= 1.0f / (1.0f + m_damping * dt);*/
}

void Actor::Draw(Renderer& renderer) {
	if (destroyed) return;

	for (auto& component : components) {
		RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(component.get());
		if (renderComponent) {
			renderComponent->Draw(renderer);
		}
	}
}

void Actor::AddComponent(std::unique_ptr<Component> component) {
	component->owner = this;
	components.push_back(std::move(component));
}

void Actor::Read(const json_t& value) {
	Object::Read(value);

	READ_DATA(value, tag);
	READ_DATA(value, lifespan);

	if (HAS_DATA(value, transform)) transform.Read(GET_DATA(value, transform));

	//read components
	if (HAS_DATA(value, components) && GET_DATA(value, components).IsArray()) {
		for (auto& componentValue : GET_DATA(value, components).GetArray()) {
			std::string type;
			READ_DATA(componentValue, type);

			auto component = Factory::Instance().Create<Component>(type);
			component->Read(componentValue);

			AddComponent(std::move(component));
		}
	}
}

void Actor::Write(json_t& value) {

}