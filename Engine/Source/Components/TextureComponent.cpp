#include "TextureComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Resources/ResourceManager.h"

void TextureComponent::Initialize() {
	if (!textureName.empty()) {
		//texture = ResourceManager::Instance().Get<Texture>();
	}
}

void TextureComponent::Update(float dt) {
	//
}

void TextureComponent::Draw(Renderer& renderer) {
	Transform transform = owner->GetTransform();
	renderer.DrawTexture(texture.get(), transform.position.x, transform.position.y, transform.rotation);
}