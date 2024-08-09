#include "Actor.h"
#include "Renderer/Model.h"
#include "Components/RenderComponent.h"

void Actor::Initialize() {
	for (auto& component : m_components) {
		component->Initialize();
	}
}

void Actor::Update(float dt) {
	if (m_lifespan != 0) {
		m_lifespan -= dt;
		if (m_lifespan <= 0) {
			m_destroyed = true;
		}
	}

	for (auto& component : m_components) {
		component->Update(dt);
	}

	m_transform.position += (m_velocity * dt);
	m_velocity *= 1.0f / (1.0f + m_damping * dt);
}

void Actor::Draw(Renderer& renderer) {
	if (m_destroyed) return;

	for (auto& component : m_components) {
		RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(component.get());
		if (renderComponent) {
			renderComponent->Draw(renderer);
		}
	}
}

void Actor::AddComponent(std::unique_ptr<Component> component) {
	component->owner = this;
	m_components.push_back(std::move(component));
}