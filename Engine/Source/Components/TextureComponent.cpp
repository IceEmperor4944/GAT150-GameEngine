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
}

void TextureComponent::Update(float dt) {
	//
}

void TextureComponent::Draw(Renderer& renderer) {
	Transform transform = owner->transform;
	renderer.DrawTexture(texture, transform, true);
}

void TextureComponent::Read(const json_t& value) {
	READ_DATA_REQUIRED(value, textureName);
}

void TextureComponent::Write(json_t& value) {

}