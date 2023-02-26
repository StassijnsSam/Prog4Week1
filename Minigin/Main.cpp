#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "Transform.h"
#include "GameObject.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//Add background
	auto background = std::make_shared<GameObject>();

	//First make transform
	auto backgroundTransform = new Transform();

	//Pass texture filename and transform to render component
	auto backgroundRenderComponent = new RenderComponent("background.tga", backgroundTransform);

	//Add the components to the gameobjects
	background.get()->AddComponent<Transform>(backgroundTransform);
	background.get()->AddComponent<RenderComponent>(backgroundRenderComponent);

	scene.Add(background);

	//go->SetTexture("background.tga");
	//scene.Add(go);

	//go = std::make_shared<dae::GameObject>();
	//go->SetTexture("logo.tga");
	//go->SetPosition(216, 180);
	//scene.Add(go);

	//auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_shared<dae::TextObject>("Programming 4 Assignment", font);
	//to->SetPosition(80, 20);
	//scene.Add(to);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}