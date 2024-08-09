#pragma once
#include "../Resources/Resource.h"
#include <SDL_ttf.h>
#include <string>

class Font : public Resource
{
public:
	Font() = default;
	~Font();

	bool Create(std::string name, ...) override;
	bool Load(const std::string& name, int fontSize);

	friend class Text;
private:
	_TTF_Font* m_ttfFont{ nullptr };
};