#pragma once
#include "Framework/Game.h"
#include "Event/EventSystem.h"
#include <memory>

class SpaceGame : public Game, Observer {
public:
	enum class State {
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDead,
		GameOver
	};
public:
	SpaceGame() = default;
	SpaceGame(Engine* engine) : Game{ engine } {}
	
	bool Initialize() override;
	void Shutdown() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

	//events
	void OnPlayerDead(const Event& event);
	void OnAddPoints(const Event& event);
private:
	std::unique_ptr<class Scene> m_scene;

	State m_state{ State::Title };
	float m_stateTimer{ 0 };
};