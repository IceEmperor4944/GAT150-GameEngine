#include "Scene.h"
#include "Actor.h"
#include "Core/Factory.h"
#include <algorithm>

void Scene::Initialize() {
	for (auto& actor : actors) {
		actor->Initialize();
	}
}

void Scene::Update(float dt) {
	//update
	for (auto& actor : actors) {
		actor->Update(dt);
	}

	actors.erase(std::remove_if(actors.begin(), actors.end(),
		[](auto& actor) {return actor->destroyed; }), actors.end());
	//std::erase_if(m_actors, [](Actor* actor) {return actor->m_destroyed; });

	/*
	//collision
	for (auto& actor1 : m_actors) {
		for (auto& actor2 : m_actors) {
			if (actor1 == actor2 || (actor1->m_destroyed || actor2->m_destroyed)) continue;

			Vector2 direction = actor1->GetTransform().position - actor2->GetTransform().position;
			float distance = direction.Length();

			float radius = actor1->GetRadius() + actor2->GetRadius();

			if (distance <= radius) {
				actor1->OnCollision(actor2.get());
				actor2->OnCollision(actor1.get());
			}
		}
	}
	*/
}

void Scene::Draw(Renderer& renderer) {
	for (auto& actor : actors) {
		actor->Draw(renderer);
	}
}

void Scene::AddActor(std::unique_ptr<Actor> actor) {
	actor->scene = this;
	actors.push_back(std::move(actor));
}

void Scene::RemoveAll() {
	actors.clear();
}

void Scene::Read(const json_t& value) {
	if (HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray()) {
		for (auto& actorValue : GET_DATA(value, actors).GetArray()){
			auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
			actor->Read(actorValue);

			AddActor(std::move(actor));
		}
	}
}

void Scene::Write(json_t& value) {
	//
}