#include "TextureComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Resources/ResourceManager.h"
#include "Engine.h"

FACTORY_REGISTER(TextureComponent)

void TextureComponent::Initialize() {
	if (!textureName.empty()) {
		texture = ResourceManager::Instance().Get<Texture>(textureName, owner->scene->engine->GetRenderer());
	}

	if (texture && source.w == 0 && source.h == 0) {
		source.x = 0;
		source.y = 0;
		source.w = static_cast<int>(texture->GetSize().x);
		source.h = static_cast<int>(texture->GetSize().y);
	}
}

void TextureComponent::Update(float dt) {
	//
}

void TextureComponent::Draw(Renderer& renderer) {
	Transform transform = owner->transform;
	renderer.DrawTexture(texture, transform, source, hflip);
}

void TextureComponent::Read(const json_t& value) {
	READ_DATA(value, textureName);
	READ_DATA(value, source);
}

void TextureComponent::Write(json_t& value) {
	//
}