#include "SpaceGame.h"
#include "Engine.h"

#include <functional>

bool SpaceGame::Initialize() {
	m_scene = std::make_unique<Scene>(m_engine);
	std::string sceneNames[] = { "Scenes/tilemap.json", "Scenes/game.json" };
	for (auto name : sceneNames) {
		//read json
		rapidjson::Document document;
		Json::Load(name, document);
		m_scene->Read(document);
	}

	m_scene->Initialize();

	SUBSCRIBE_OBSERVER(PlayerDead, SpaceGame::OnPlayerDead);
	SUBSCRIBE_OBSERVER(AddPoints, SpaceGame::OnAddPoints);

    return true;
}

void SpaceGame::Shutdown() {
	m_scene->RemoveAll(true);
}

void SpaceGame::Update(float dt) {
    /* {
        switch (m_state) {
        case State::Title:
            if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
                m_state = State::StartGame;
            }
            break;
        case State::StartGame:
            m_engine->GetAudio().PlaySound("song.wav");

            m_state = State::StartLevel;
            break;
        case State::StartLevel:
            m_scene->RemoveAll(true);
            {
                auto player = Factory::Instance().Create<Actor>("player");
                player->transform.position = Vector2{ 60, 60 };
                m_scene->AddActor(std::move(player), true);
            }

            /*m_spawnTime = 3;
            m_spawnTimer = m_spawnTime;

            m_state = State::Game;
            break;
        case State::Game:
            //m_spawnTimer -= dt;
            //if (m_spawnTimer <= 0) {
            //    m_spawnTime *= 0.99f;
            //    m_spawnTimer = m_spawnTime;

            //    //create enemy
            //    auto* enemyModel = new Model{ GameData::enemyPoints, Color{1, 0, 0} };
            //    auto enemy = std::make_unique<Enemy>(400.0f, Transform{ Vector2{random(RENDERER.GetWidth()), random(RENDERER.GetHeight())}, 0, 2 }, enemyModel);
            //    enemy->SetDamping(1.0f);
            //    enemy->SetTag("Enemy");
            //    m_scene->AddActor(std::move(enemy));

            //    // create pickup
            //    auto* pickupModel = new Model{ GameData::pickupPoints, Color{1, 0, 1} };
            //    auto pickup = std::make_unique<Pickup>(Transform{ Vector2{random(RENDERER.GetWidth()), random(RENDERER.GetHeight())}, 0, 2 }, pickupModel, 1);
            //    pickup->SetTag("Pickup");
            //    m_scene->AddActor(std::move(pickup));

            //    m_pickupCount--;
            //}

            //if (m_pickupCount == 5) {
            //    // create bomb
            //    auto* bombModel = new Model{ GameData::pickupPoints, Color{0, 1, 0} };
            //    auto bombPick = std::make_unique<Pickup>(Transform{ Vector2{random(RENDERER.GetWidth()), random(RENDERER.GetHeight())}, 0, 2 }, bombModel, 2);
            //    bombPick->SetTag("Pickup");
            //    m_scene->AddActor(std::move(bombPick));

            //    m_pickupCount = 4;
            //}

            //if (m_pickupCount == 1) {
            //    // create splitter
            //    auto* shotModel = new Model{ GameData::pickupPoints, Color{0, 0, 1} };
            //    auto shot = std::make_unique<Pickup>(Transform{ Vector2{random(RENDERER.GetWidth()), random(RENDERER.GetHeight())}, 0, 2 }, shotModel, 3);
            //    shot->SetTag("Pickup");
            //    m_scene->AddActor(std::move(shot));

            //    m_pickupCount = 11;
            //}

            break;
        case State::PlayerDead:
            m_stateTimer -= dt;
            if (m_stateTimer <= 0) m_state = State::StartLevel;
            break;
        case State::GameOver:
            m_scene->RemoveAll(true);

            m_stateTimer -= dt;
            if (m_stateTimer <= 0) m_state = State::Title;
            break;
        default:
            break;
        }
    }*/
	
	/*auto bat = Factory::Instance().Create<Actor>("bat");
	bat->transform.position = Vector2{ randomf(1000), randomf(1000) };
	m_scene->AddActor(std::move(bat), true);*/ //adds bats every frame, use for making shit happen

	/*if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
		m_scene->RemoveAll(false);
	}*/


	
	m_scene->Update(dt);
}

void SpaceGame::Draw(Renderer& renderer) {
	m_scene->Draw(m_engine->GetRenderer());
}

void SpaceGame::OnPlayerDead(const Event& event) {
    m_stateTimer = 5.0f;
    //m_engine->GetAudio().PlaySound("trombone.wav");
    m_state = State::GameOver;
	std::cout << "game player dead\n";
}

void SpaceGame::OnAddPoints(const Event& event) {
	m_score += std::get<int>(event.data);
	std::cout << m_score << std::endl;
}