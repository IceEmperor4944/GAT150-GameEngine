#include "SpaceGame.h"
#include "Engine.h"

#include <functional>

bool SpaceGame::Initialize() {
	// create json document from the json file contents
	rapidjson::Document document;
	Json::Load("Scenes/scene.json", document);

	m_scene = std::make_unique<Scene>(m_engine);
	m_scene->Read(document);
	m_scene->Initialize();

	SUBSCRIBE_OBSERVER(PlayerDead, SpaceGame::OnPlayerDead);
	SUBSCRIBE_OBSERVER(AddPoints, SpaceGame::OnAddPoints);

    return true;
}

void SpaceGame::Shutdown() {
	m_scene->RemoveAll();
}

void SpaceGame::Update(float dt) {
	m_scene->Update(dt);
}

void SpaceGame::Draw(Renderer& renderer) {
	m_scene->Draw(m_engine->GetRenderer());
}

void SpaceGame::OnPlayerDead(const Event& event) {
	std::cout << "game player dead\n";
}

void SpaceGame::OnAddPoints(const Event& event) {
	m_score += std::get<int>(event.data);
	std::cout << m_score << std::endl;
}