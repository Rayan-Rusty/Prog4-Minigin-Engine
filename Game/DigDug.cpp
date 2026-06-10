
#include "DigDug.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include <algorithm>
#include "InputManager.h"
#include "MoveCommand.h"
#include "EnemySpawnerComponent.h"
#include "EnemyTraits.h"

#include "TilemapComponent.h"
#include "Utils.h"
#include "MenuNavigateCommand.h"
#include "Menu/MenuMarker.h"
#include "Menu/Events/System/MenuNavigateSystem.h"


//TODO ASYNC noise
//TODO remove FPS object


void DigDug::Game::Init()
{
    dae::SceneManager::GetInstance().RegisterScene(0, [this]{ InitializeMenuScreen(); });
    dae::SceneManager::GetInstance().RegisterScene(1, [this]{ InitFirstLevel(); });

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
    auto scene = &dae::SceneManager::GetInstance().CreateScene();

    //========================
    //===== Background =======
    //========================
    auto Background = Utils::CreateBackgroundObject("MainMenu/Background.png");
    Background->GetTransform().SetScale(glm::vec3{2, 2, 2});
    Background->GetTransform().SetWorldPosition(glm::vec3{0, 0, 0});

    //========================
    //===== Arrow =======
    //========================
    auto Marker = Utils::CreateBackgroundObject("MainMenu/Marker.png");
    Marker->GetTransform().SetScale(glm::vec3{2, 2, 2});
    Marker->GetTransform().SetWorldPosition(glm::vec3{512 / 2 - 100, 205, 0});

    auto markerComp  = std::make_unique<MenuMarker>(Marker.get());
    markerComp->AddPosition(glm::vec3{512 / 2 - 100, 205, 0}); // Single Player
    markerComp->AddPosition(glm::vec3{512 / 2 - 100, 235, 0}); // Multiplayer
    markerComp->AddPosition(glm::vec3{512 / 2 - 100, 265, 0}); // Options


    Marker->AddComponent(std::move(markerComp));


    auto menuSystem = std::make_unique<MenuNavigateSystem>(Marker.get());
    scene->StoreSystem(std::move(menuSystem));

    auto menuUp = std::make_unique<dae::MenuNavigateCommand>(Marker.get() , 1);

    dae::InputManager::GetInstance().AddCommandBinding(
        SDL_SCANCODE_W,
        std::move(menuUp),
        dae::InputManager::KeyState::Down
    );

    auto menuDown = std::make_unique<dae::MenuNavigateCommand>(Marker.get() , -1);

    dae::InputManager::GetInstance().AddCommandBinding(
        SDL_SCANCODE_S,
        std::move(menuDown),
        dae::InputManager::KeyState::Down
    );

    scene->Add(std::move(Background));
    scene->Add(std::move(Marker));

}


void DigDug::Game::InitFirstLevel()
{
    CollisionManager::GetInstance().Clear();
    auto Scene = &dae::SceneManager::GetInstance().CreateScene();

    auto player = Utils::CreatePlayer();

    Scene->Add(std::move(player));
    auto Tilemap = Utils::CreateTilemap("Sprites/Block.png", "Data/Sprites/IndexedFile.png");

    Tilemap->GetTransform().SetWorldPosition(glm::vec3{0, 16*2, 0});


    Scene->Add(std::move(Tilemap));

    auto SpawnerObject = std::make_unique<dae::GameObject>();
    auto spawner = std::make_unique<EnemySpawnerComponent<PookaTraits>>(SpawnerObject.get(), Scene);
    spawner->LoadFromFile("Data/Sprites/EnemyMap.png");

    SpawnerObject->AddComponent(std::move(spawner));
    SpawnerObject->GetTransform().SetWorldPosition(glm::vec3{0, 0, 0});

    Scene->Add(std::move(SpawnerObject));

    Scene->SortByLayer();

}
