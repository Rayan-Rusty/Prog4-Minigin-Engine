
#include "DigDug.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "EnemySpawnerComponent.h"
#include "LevelComponent.h"
#include "PlayerBehaviour.h"

#include "Utils.h"

#include "ScoreComponent.h"
#include "PumpBehaviour.h"
#include "SoundEventListener.h"


//TODO ASYNC noise
//TODO remove FPS object


void DigDug::Game::Init()
{

    dae::SceneManager::GetInstance().RegisterScene(0, [this]{ InitializeMenuScreen(); });
    dae::SceneManager::GetInstance().RegisterScene(1, [this]{ InitFirstLevel(); });
    dae::SceneManager::GetInstance().RegisterScene(2, [this]{ HighScoreLevel(); });
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

    auto* Scene = dae::SceneManager::GetInstance().GetActiveScene();
    Scene->Clear();
    CollisionManager::GetInstance().Clear();
    Scene->Clear();

    auto soundListener = std::make_unique<dae::SoundEventListener>();
    Scene->StoreSystem(std::move(soundListener));
    auto Tilemap = Utils::CreateTilemap("Sprites/Blocks.png", "");
    Tilemap->GetTransform().SetWorldPosition(glm::vec3{0, 0, 0});
    Scene->Add(std::move(Tilemap));

    auto player = Utils::CreatePlayer();
    Scene->Add(std::move(player));

    auto levelMgr = Utils::CreateLevelManager(Utils::CreateLevelList());
    auto* levelComp = levelMgr->GetComponent<DigDug::LevelComponent>();
    Scene->Add(std::move(levelMgr));
    auto scoreObj = Utils::CreateText("Score: 0", glm::vec3{10, 10, 0});
    scoreObj->AddComponent(std::make_unique<DigDug::ScoreComponent>(scoreObj.get()));
    Scene->Add(std::move(scoreObj));
    levelComp->LoadCurrentLevel();


    auto playerObjs = Scene->GetObjectByTag(static_cast<int>(DigDug::GameTag::Player));
    if (!playerObjs.empty())
    {
        auto pump = Utils::CreatePump(playerObjs[0]);
        auto* pumpRaw = pump.get();
        Scene->Add(std::move(pump));
        pumpRaw->SetParent(playerObjs[0], false);

        if (auto* pb = pumpRaw->GetComponent<DigDug::PumpBehaviour>())
            Scene->GetEventBus().AddListener(pb);
        if (auto* pb = playerObjs[0]->GetComponent<DigDug::PlayerBehaviour>())
            Scene->GetEventBus().AddListener(pb);
    }




}

void DigDug::Game::HighScoreLevel()
{

    auto* scene = dae::SceneManager::GetInstance().GetActiveScene();
    scene->Clear();



    auto bg = Utils::CreateBackgroundObject("Sprites/HighScoreScreen/BackgroundScore.png");
    bg->GetTransform().SetScale(glm::vec3{2, 2, 2});
    scene->Add(std::move(bg));

    //event passed arg
    auto hsObj = Utils::CreateHighscoreObject(scene, DigDug::ScoreComponent::s_LastScore);
    scene->Add(std::move(hsObj));

}
