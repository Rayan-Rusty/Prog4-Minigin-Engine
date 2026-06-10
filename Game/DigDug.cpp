
#include "DigDug.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "EnemySpawnerComponent.h"
#include "EnemyTraits.h"
#include "TilemapComponent.h"
#include "Utils.h"




//TODO ASYNC noise
//TODO remove FPS object


void DigDug::Game::Init()
{

    dae::SceneManager::GetInstance().RegisterScene(0, [this]{ InitializeMenuScreen(); });
    dae::SceneManager::GetInstance().RegisterScene(1, [this]{ InitFirstLevel(); });
    dae::SceneManager::GetInstance().SetActiveScene(0);
}

void DigDug::Game::Update(float deltaTime)
{
    dae::SceneManager::GetInstance().Update(deltaTime);

}

void DigDug::Game::Draw() const
{
    dae::SceneManager::GetInstance().Render();
}


void DigDug::Game::InitializeMenuScreen()
{
    auto* scene = dae::SceneManager::GetInstance().GetActiveScene();

    auto Background = Utils::CreateBackgroundObject("MainMenu/Background.png");
    Background->GetTransform().SetScale(glm::vec3{2, 2, 2});
    Background->GetTransform().SetWorldPosition(glm::vec3{0, 0, 0});
    auto Marker = Utils::CreateMenuMarker();

    scene->Add(std::move(Background));
    scene->Add(std::move(Marker));

}


void DigDug::Game::InitFirstLevel()
{
    CollisionManager::GetInstance().Clear();
    auto* Scene = dae::SceneManager::GetInstance().GetActiveScene();

    auto player = Utils::CreatePlayer();

    Scene->Add(std::move(player));
    auto Tilemap = Utils::CreateTilemap("Sprites/Block.png", "Data/Sprites/IndexedFile.png");

    Tilemap->GetTransform().SetWorldPosition(glm::vec3{0, 0, 0});


    Scene->Add(std::move(Tilemap));

    auto SpawnerObject = std::make_unique<dae::GameObject>();

    auto spawner = std::make_unique<EnemySpawnerComponent<PookaTraits>>(SpawnerObject.get(), Scene);
    spawner->LoadFromFile("Data/Sprites/EnemyMap.png");

    SpawnerObject->AddComponent(std::move(spawner));

    Scene->Add(std::move(SpawnerObject));

    Scene->SortByLayer();

}
