#include "TilemapComponent.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"

FACTORY_REGISTER(TilemapComponent)

void TilemapComponent::Initialize() {
	for (int i = 0; i < tiles.size(); i++) {
		int index = tiles[i];
		if (index == 0) continue;
		std::string name = tileNames[index];
		auto tile = Factory::Instance().Create<Actor>(name);
		if (tile) {
			int x = i % numColumns;
			int y = i / numColumns;

			tile->transform.position = owner->transform.position + Vector2{ x, y } * tileSize;
			owner->scene->AddActor(std::move(tile), true);
		}
	}
}

void TilemapComponent::Update(float dt) {
	//
}

void TilemapComponent::Read(const json_t& value) {
	READ_DATA(value, numColumns);
	READ_DATA(value, numRows);
	READ_DATA(value, tileSize);
	READ_DATA(value, tileNames);
	READ_DATA(value, tiles);
}

void TilemapComponent::Write(json_t& value) {
	//
}