#pragma once
#include "Component.h"
#include <vector>

class TilemapComponent : public Component {
public:
	TilemapComponent() = default;

	CLASS_DECLARATION(TilemapComponent)
	CLASS_PROTOTYPE(TilemapComponent)
	
	void Initialize() override;
	void Update(float dt) override;
public:
	int numColumns;
	int numRows;
	Vector2 tileSize{ 0,0 };

	std::vector<std::string> tileNames;
	std::vector<int> tiles;
};