#include "Font.h"
#include <iostream>

Font::~Font()
{
	if (m_ttfFont != nullptr)
	{
		TTF_CloseFont(m_ttfFont);
	}
}

bool Font::Load(const std::string& name, int fontSize)
{
	m_ttfFont = TTF_OpenFont(name.c_str(), fontSize);
	if (m_ttfFont == nullptr)
	{
		std::cerr << "Could not load font: " << name << std::endl;
		return false;
	}

	return true;
}

bool Font::Create(std::string name, ...)
{
	va_list args;
	va_start(args, name);
	int fontSize = va_arg(args, int);
	va_end(args);

	return Load(name, fontSize);
}