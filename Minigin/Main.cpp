#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "FPSCounter.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "RotatorComponent.h"
#include "TextComponent.h"
#include "TextureComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	const auto pFont{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	const auto pBackgroundTexture{ dae::ResourceManager::GetInstance().LoadTexture("background.tga") };
	const auto pLogoTexture{ dae::ResourceManager::GetInstance().LoadTexture("logo.tga") };

	// BACKGROUND
	auto go = std::make_shared<dae::GameObject>();
	go->Init();
	go->AddComponent<dae::TextureComponent>()->SetTexture(pBackgroundTexture);
	scene.Add(go);

	// DAE LOGO
	go = std::make_shared<dae::GameObject>();
	go->Init();
	go->GetComponent<dae::Transform>()->SetWorldPosition(216, 180);
	go->AddComponent<dae::TextureComponent>()->SetTexture(pLogoTexture);
	go->AddComponent<dae::FPSCounter>();
	scene.Add(go);

	// TEXT
	go = std::make_shared<dae::GameObject>();
	go->Init();
	go->GetComponent<dae::Transform>()->SetWorldPosition(80, 20);
	go->AddComponent<dae::TextureComponent>();
	const auto pHeaderText{ go->AddComponent<dae::TextComponent>() };
	pHeaderText->SetFont(pFont);
	pHeaderText->SetText("Programming 4 Assignment");
	scene.Add(go);

	// FPS COUNTER
	go = std::make_shared<dae::GameObject>();
	go->Init();
	go->GetComponent<dae::Transform>()->SetWorldPosition(0.0f, 0.0f);
	go->AddComponent<dae::TextureComponent>();
	go->AddComponent<dae::FPSCounter>();
	const auto pText{ go->AddComponent<dae::TextComponent>() };
	pText->SetFont(pFont);
	scene.Add(go);

	// EMPTY OBJECT TO USE AS PIVOT
	auto pPivot = std::make_shared<dae::GameObject>();
	pPivot->Init();
	pPivot->GetComponent<dae::Transform>()->SetWorldPosition(300, 300);
	scene.Add(pPivot);

	// Create a GO that renders the main character and rotates around the empty pivot object
	const auto pCharacter = std::make_shared<dae::GameObject>();
	pCharacter->Init();
	pCharacter->SetParent(pPivot);
	pCharacter->AddComponent<dae::RotatorComponent>()->SetRotateSpeed(-180.0f);
	pCharacter->AddComponent<dae::TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("MainCharacter.png"));
	scene.Add(pCharacter);

	// Create a GO that renders the enemy and rotates around the character at double speed
	const auto pEnemy = std::make_shared<dae::GameObject>();
	pEnemy->Init();
	pEnemy->SetParent(pCharacter);
	pEnemy->AddComponent<dae::RotatorComponent>()->SetRotateSpeed(360.0f);
	pEnemy->AddComponent<dae::TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Enemy.png"));
	scene.Add(pEnemy);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}