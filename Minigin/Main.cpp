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

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//Add background
	auto background = std::make_shared<GameObject>();

	background.get()->AddComponent<Transform>();

	background.get()->AddComponent<RenderComponent>("background.tga");
	//backgroundRenderComponent->SetTexture("background.tga");

	scene.Add(background);

	//Add logo
	auto logo = std::make_shared<GameObject>();

	logo.get()->AddComponent<Transform>(glm::vec2{216, 180});
	//logoTransform->SetPosition(216, 180);

	logo.get()->AddComponent<RenderComponent>("logo.tga");
	//logoRenderComponent->SetTexture("logo.tga");

	scene.Add(logo);

	//Add text
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto title = std::make_shared<GameObject>();

	title.get()->AddComponent<Transform>(glm::vec2{80, 20});
	//titleTransform->SetPosition(80, 20);

	title.get()->AddComponent<TextComponent>("Programming 4 Assignment", font);
	//titleTextComponent->SetText("Programming 4 Assignment");
	//titleTextComponent->SetFont(font);

	title.get()->AddComponent<RenderComponent>();

	scene.Add(title);

	//Add FPS counter
	auto fontFPS = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);

	auto FPSCounter = std::make_shared<GameObject>();

	FPSCounter.get()->AddComponent<Transform>(glm::vec2{10, 10});
	//FPSTransform->SetPosition(10, 10);

	FPSCounter.get()->AddComponent<TextComponent>("0 FPS", fontFPS, SDL_Color{255, 255, 0});
	//FPSTextComponent->SetText("0 FPS");
	//FPSTextComponent->SetFont(fontFPS);
	//FPSTextComponent->SetColor({ 255, 255, 0 });

	FPSCounter.get()->AddComponent<FPSComponent>();
	
	FPSCounter.get()->AddComponent<RenderComponent>();

	scene.Add(FPSCounter);

	//Initialize the scene to link the components together (components that require other components to work)
	scene.Initialize();
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}