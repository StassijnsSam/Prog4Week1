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
#include "TextComponent.h"
#include "FPSComponent.h"
#include "RotatorComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//Add background
	auto background = std::make_shared<dae::GameObject>();

	background.get()->AddComponent<dae::Transform>();
	background.get()->AddComponent<dae::RenderComponent>("background.tga");

	scene.Add(background);

	//Add logo
	auto logo = std::make_shared<dae::GameObject>();

	logo.get()->AddComponent<dae::Transform>(glm::vec2{216, 180});
	logo.get()->AddComponent<dae::RenderComponent>("logo.tga");

	scene.Add(logo);

	//Add text
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto title = std::make_shared<dae::GameObject>();

	title.get()->AddComponent<dae::Transform>(glm::vec2{80, 20});
	title.get()->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
	title.get()->AddComponent<dae::RenderComponent>();

	scene.Add(title);

	//Add FPS counter
	auto fontFPS = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	auto FPSCounter = std::make_shared<dae::GameObject>();

	FPSCounter.get()->AddComponent<dae::Transform>(glm::vec2{10, 10});
	FPSCounter.get()->AddComponent<dae::TextComponent>("0 FPS", fontFPS, SDL_Color{255, 255, 0});
	FPSCounter.get()->AddComponent<dae::FPSComponent>();
	FPSCounter.get()->AddComponent<dae::RenderComponent>();

	scene.Add(FPSCounter);

	//Add central ghost
	auto ghost1 = std::make_shared<dae::GameObject>();

	ghost1.get()->AddComponent<dae::Transform>(glm::vec2{ 310.f, 300.f });
	ghost1.get()->AddComponent<dae::RenderComponent>("GhostPink.png");
	ghost1.get()->AddComponent<dae::RotatorComponent>(240.f, 20.f);

	scene.Add(ghost1);

	//Add second ghost
	auto ghost2 = std::make_shared<dae::GameObject>();

	ghost2.get()->AddComponent<dae::Transform>(glm::vec2{ 0.f, 0.f });	
	ghost2.get()->AddComponent<dae::RenderComponent>("GhostDead.png");
	ghost2.get()->AddComponent<dae::RotatorComponent>(240.f, 20.f);
	
	//Make ghost2 a child
	ghost2.get()->SetParent(ghost1.get(), false);

	scene.Add(ghost2);

	//Initialize the scene to link the components together (components that require other components to work)
	scene.Initialize();
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}