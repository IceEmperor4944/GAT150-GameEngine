#include "Engine.h"

#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[]) {
	Factory::Instance().Register<Actor>(Actor::GetTypeName());
	Factory::Instance().Register<TextureComponent>(TextureComponent::GetTypeName());

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	// !! this code is not neccessary, it just shows the contents of the file !!
	std::string buffer;
	File::ReadFile("text.txt", buffer);
	// show the contents of the json file
	std::cout << buffer << std::endl;

	// create json document from the json file contents
	rapidjson::Document document;
	Json::Load("text.txt", document);

	// read the data from the json
	std::string name;
	int age;
	float speed;
	bool isAwake;
	Vector2 position;
	Color color;

	READ_DATA(document, name);
	READ_DATA(document, age);
	READ_DATA(document, speed);
	READ_DATA(document, isAwake);
	READ_DATA(document, position);
	READ_DATA(document, color);

	// show the data
	std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
	std::cout << position.x << " " << position.y << std::endl;
	std::cout << color.r << " " << color.g << " " << color.b << " " << color.a << std::endl;
	{
		res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("strawberry.bmp", engine->GetRenderer());
		res_t<Font> font = ResourceManager::Instance().Get<Font>("fonts/arcadeclassic.ttf", 12);
		std::unique_ptr<Text> text = std::make_unique<Text>(font);
		text->Create(engine->GetRenderer(), "Hello!", { 1, 1, 0, 1 });

		Transform t{ { 30, 30 } };
		auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
		actor->SetTransform(Transform{ {20,20} });
		auto component = Factory::Instance().Create<TextureComponent>(TextureComponent::GetTypeName());
		component->texture = texture;
		actor->AddComponent(std::move(component));

		while (!engine->IsQuit())
		{
			engine->Update();

			actor->Update(engine->GetTime().GetDeltaTime());

			// clear screen
			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();

			text->Draw(engine->GetRenderer(), 200, 200);
			//engine->GetRenderer().DrawTexture(texture.get(), 50, 50, 0);
			actor->Draw(engine->GetRenderer());

			engine->GetRenderer().EndFrame();
		}
	}

	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}