#include "TextComponent.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"


void TextComponent::Initialize() {
	if (!fontName.empty()) {
		auto font = ResourceManager::Instance().Get<Font>(fontName, fontSize);
		m_text = std::make_unique<Text>(font);
	}
}

void TextComponent::Update(float dt) {

}

void TextComponent::Draw(Renderer& renderer) {
	if (textChanged) {
		m_text->Create(renderer, text, color);
		textChanged = false;
	}

	renderer.DrawTexture(m_text->GetTexture(), owner->transform);
}

void TextComponent::SetText(const std::string& text) {
	if (this->text != text) {
		this->text = text;
		textChanged = true;
	}
}

void TextComponent::Read(const json_t& value) {
	READ_DATA(value, text);
	READ_DATA(value, fontName);
	READ_DATA(value, fontSize);
	READ_DATA(value, color);
}

void TextComponent::Write(json_t& value) {
	
}