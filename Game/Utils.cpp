//
// Created by omen on 05/05/2026.
//

#include "Utils.h"

#include "InputManager.h"
#include "Keyboard.h"
#include "MoveCommand.h"
#include "MovementComponent.h"
#include "PlayerBehaviour.h"
#include "RenderComponent.h"
#include "SpriteAnimationComponent.h"
#include "CollisionComponent.h"
#include "CollisionManager.h"
#include "FygarBehaviour.h"
#include "LevelComponent.h"
#include "MenuMarker.h"
#include "MenuNavigateCommand.h"
#include "PookaBehaviour.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include "GameLayers.h"
#include "TilemapComponent.h"
#include "BlockBehaviour.h"
#include "AttackCommand.h"
#include "PlayerMoveCommand.h"
#include "ConfirmedCommand.h"
#include "PlayerMovement.h"
#include "PookaMovement.h"
#include "PumpBehaviour.h"
#include "LevelStruct.h"
#include "HighScoreComponent.h"
#include "HighScoreConfirmCommand.h"
#include "HighScoreNavigatecommand.h"
#include "FygarMovement.h"

std::unique_ptr<dae::GameObject> Utils::CreateAnimatedSpriteObject(const std::string &TexturePath, int rows, int cols, int layer, int tag )
{
    auto obj = std::make_unique<dae::GameObject>(layer , tag);

    auto renderComp = std::make_unique<dae::RenderComponent>(obj.get());
    renderComp->SetTextureFilePath(TexturePath);

    obj->AddComponent(std::move(renderComp));

    obj->AddComponent(std::make_unique<dae::SpriteAnimationComponent>( obj.get(), rows , cols ));




    return std::move(obj);
}

std::unique_ptr<dae::GameObject> Utils::CreatePlayerCharacter(const std::string &TexturePath, int rows, int cols)
{

    auto obj = std::make_unique<dae::GameObject>(
        static_cast<int>(DigDug::Layer::Foreground),
        static_cast<int>(DigDug::GameTag::Player)
    );

    auto renderComp = std::make_unique<dae::RenderComponent>(obj.get());
    renderComp->SetTextureFilePath(TexturePath);
    obj->AddComponent(std::move(renderComp));

    obj->AddComponent(std::make_unique<dae::SpriteAnimationComponent>(obj.get(), rows, cols));

    obj->AddComponent(std::make_unique<DigDug::PlayerMovement>(obj.get()));

    dae::InputManager::GetInstance().AddCommandBinding(SDL_SCANCODE_A,
        std::make_unique<DigDug::PlayerMoveCommand>(obj.get(), glm::ivec2{-1, 0}),
        dae::InputManager::KeyState::Held);
    dae::InputManager::GetInstance().AddCommandBinding(SDL_SCANCODE_D,
        std::make_unique<DigDug::PlayerMoveCommand>(obj.get(), glm::ivec2{1, 0}),
        dae::InputManager::KeyState::Held);
    dae::InputManager::GetInstance().AddCommandBinding(SDL_SCANCODE_W,
        std::make_unique<DigDug::PlayerMoveCommand>(obj.get(), glm::ivec2{0, -1}),
        dae::InputManager::KeyState::Held);
    dae::InputManager::GetInstance().AddCommandBinding(SDL_SCANCODE_S,
        std::make_unique<DigDug::PlayerMoveCommand>(obj.get(), glm::ivec2{0, 1}),
        dae::InputManager::KeyState::Held);

    dae::InputManager::GetInstance().AddCommandBinding(dae::GamepadButton::DPadLeft,
        std::make_unique<DigDug::PlayerMoveCommand>(obj.get(), glm::ivec2{-1, 0}),
        dae::InputManager::KeyState::Held);
    dae::InputManager::GetInstance().AddCommandBinding(dae::GamepadButton::DPadRight,
        std::make_unique<DigDug::PlayerMoveCommand>(obj.get(), glm::ivec2{1, 0}),
        dae::InputManager::KeyState::Held);
    dae::InputManager::GetInstance().AddCommandBinding(dae::GamepadButton::DPadUp,
        std::make_unique<DigDug::PlayerMoveCommand>(obj.get(), glm::ivec2{0, -1}),
        dae::InputManager::KeyState::Held);
    dae::InputManager::GetInstance().AddCommandBinding(dae::GamepadButton::DPadDown,
        std::make_unique<DigDug::PlayerMoveCommand>(obj.get(), glm::ivec2{0, 1}),
        dae::InputManager::KeyState::Held);

    return obj;
}


std::unique_ptr<dae::GameObject> Utils::CreateBackgroundObject(const std::string &TexturePath, int tag)
{
    auto obj = std::make_unique<dae::GameObject>(static_cast<int>(DigDug::Layer::Foreground), tag);

    auto renderComp = std::make_unique<dae::RenderComponent>(obj.get());
    renderComp->SetTextureFilePath(TexturePath);

    obj->AddComponent(std::move(renderComp));



    return obj;
}

std::unique_ptr<dae::GameObject> Utils::CreateFygar()
{
    auto fygar = Utils::CreateEnemy("Sprites/FygarSprites.png", 8, 8);
    fygar->GetTransform().SetScale(glm::vec3{2, 2, 2});

    auto* col = fygar->GetComponent<dae::CollisionComponent>();
    if (col)
    {
        col->SetSize(16.f, 16.f);
        col->SetLayer(dae::CollisionComponent::Layer::Enemy);
    }

    auto fygarMovement = std::make_unique<DigDug::FygarMovement>(fygar.get());
    fygar->AddComponent(std::move(fygarMovement));

    auto fygarAI = std::make_unique<DigDug::FygarBehaviour>(fygar.get());
    fygar->AddComponent(std::move(fygarAI));

    return fygar;
}

std::unique_ptr<dae::GameObject> Utils::CreatePooka()
{

    auto pooka {Utils::CreateEnemy("Sprites/PookaSprites.png" ,6 , 7 )};
    pooka->GetTransform().SetScale(glm::vec3{2, 2, 2});
    auto* col = pooka->GetComponent<dae::CollisionComponent>();
    if (col)
    {
        col->SetSize(16.f, 16.f);

        col->SetLayer(dae::CollisionComponent::Layer::Enemy);
    }

    auto pookaMovement = std::make_unique<DigDug::PookaMovement>(pooka.get());
    pooka->AddComponent(std::move(pookaMovement));

    auto pookaAI = std::make_unique<DigDug::PookaBehaviour>(pooka.get());
    pooka->AddComponent(std::move(pookaAI));

    return pooka;

}

std::unique_ptr<dae::GameObject> Utils::CreatePlayer()
{
    auto player = Utils::CreatePlayerCharacter("Sprites/PlayerSprites.png", 3, 8);
    player->GetTransform().SetWorldPosition(glm::vec3{16 * 12, 16 * 14, 0});
    player->GetTransform().SetScale(glm::vec3{2, 2, 2});

    auto PlayerAI = std::make_unique<DigDug::PlayerBehaviour>(player.get());
    player->AddComponent(std::move(PlayerAI));

    auto playerCol = std::make_unique<dae::CollisionComponent>(player.get());
    playerCol->SetOffset(2.f, 2.f);
    playerCol->SetSize(12.f, 12.f);
    player->AddComponent(std::move(playerCol));
    CollisionManager::GetInstance().Register(player->GetComponent<dae::CollisionComponent>());


    return player;
}
// Utils.cpp
std::unique_ptr<dae::GameObject> Utils::CreatePump(dae::GameObject* player)
{

    auto pump = std::make_unique<dae::GameObject>(static_cast<int>(DigDug::Layer::Foreground) , static_cast<int>(DigDug::GameTag::Pump));

    auto renderComp = std::make_unique<dae::RenderComponent>(pump.get());
    renderComp->SetTextureFilePath("Sprites/Player/Pump.png");

    pump->AddComponent(std::move(renderComp));

    pump->AddComponent(std::make_unique<dae::SpriteAnimationComponent>( pump.get(), 1 , 2 ));



    pump->GetTransform().SetScale(glm::vec3{2, 2, 2});

    auto pumpCol = std::make_unique<dae::CollisionComponent>(pump.get());
    pumpCol->SetSize(32.f, 12.f);
    pumpCol->SetOffset(0.f, 2.f);
    pump->AddComponent(std::move(pumpCol));
    CollisionManager::GetInstance().Register(pump->GetComponent<dae::CollisionComponent>());

    pump->AddComponent(std::make_unique<DigDug::PumpBehaviour>(pump.get()));
    dae::InputManager::GetInstance().AddCommandBinding(
        SDL_SCANCODE_SPACE,
        std::make_unique<DigDug::AttackCommand>(player),
        dae::InputManager::KeyState::Down
    );
    dae::InputManager::GetInstance().AddCommandBinding(
        dae::GamepadButton::A,
        std::make_unique<DigDug::AttackCommand>(player),
        dae::InputManager::KeyState::Down
    );

    return pump;
}

std::unique_ptr<dae::GameObject> Utils::CreateText(std::string text, glm::vec3 pos )
{
    auto obj = std::make_unique<dae::GameObject>(
        static_cast<int>(DigDug::Layer::UI),
        static_cast<int>(DigDug::GameTag::UI)
    );

    obj->GetTransform().SetWorldPosition(pos);
    obj->AddComponent(std::make_unique<dae::RenderComponent>(obj.get()));
    obj->AddComponent(std::make_unique<dae::TextComponent>(
        obj.get(),
        text,
        dae::ResourceManager::GetInstance().LoadFont("Fonts/Emulogic-zrEw.ttf", 18)
    ));

    return obj;
}

std::unique_ptr<dae::GameObject> Utils::CreateEnemy(const std::string& TexturePath, int rows, int cols)
{
    auto obj = std::make_unique<dae::GameObject>(
        static_cast<int>(DigDug::Layer::Foreground),
        static_cast<int>(DigDug::GameTag::Enemy)
    );

    auto renderComp = std::make_unique<dae::RenderComponent>(obj.get());
    renderComp->SetTextureFilePath(TexturePath);
    obj->AddComponent(std::move(renderComp));

    obj->AddComponent(std::make_unique<dae::SpriteAnimationComponent>(obj.get(), rows, cols));

    auto col = std::make_unique<dae::CollisionComponent>(obj.get());
    obj->AddComponent(std::move(col));
    CollisionManager::GetInstance().Register(obj->GetComponent<dae::CollisionComponent>());

    return obj;
}
std::unique_ptr<dae::GameObject> Utils::CreateTilemap(const std::string& texturePath, const std::string& dataPath)
{
    auto obj = std::make_unique<dae::GameObject>(static_cast<int>(DigDug::Layer::Background), static_cast<int>(DigDug::GameTag::TilemapComponent));




    auto tilemapComp = std::make_unique<DigDug::TilemapComponent>(obj.get());

    obj->GetTransform().SetScale(glm::vec3{2, 2, 2});
    tilemapComp->AddTexture(texturePath);
    tilemapComp->LoadFromFile(dataPath);

    obj->AddComponent(std::move(tilemapComp));


    return obj;
}

std::unique_ptr<dae::GameObject> Utils::CreateTile(float worldX, float worldY, float , float , int layer)
{
    auto obj = std::make_unique<dae::GameObject>(
        static_cast<int>(DigDug::Layer::Background),
        static_cast<int>(DigDug::GameTag::Tilemap)
    );

    auto renderComp = std::make_unique<dae::RenderComponent>(obj.get());
    renderComp->SetTextureFilePath("Sprites/Blocks.png");
    obj->AddComponent(std::move(renderComp));

    obj->AddComponent(std::make_unique<dae::SpriteAnimationComponent>(obj.get(), 4, 2));

    obj->GetTransform().SetWorldPosition(glm::vec3{worldX, worldY, 0});
    obj->GetTransform().SetScale(glm::vec3{2, 2, 2});

    auto col = std::make_unique<dae::CollisionComponent>(obj.get());
    col->SetSize(16, 16);
    obj->AddComponent(std::move(col));

    CollisionManager::GetInstance().Register(obj->GetComponent<dae::CollisionComponent>());

    auto BlockComp = std::make_unique<DigDug::BlockBehaviour>(obj.get());
    obj->AddComponent(std::move(BlockComp));

    if (auto* spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
    {
        float frameW = 16.f;
        float frameH = 16.f;
        int clampedLayer = std::clamp(layer, 0, 3);
        spriteComp->SetAnimation(
            {{ 0, frameH * clampedLayer, frameW, frameH }},
            0.f, false
        );
    }

    return obj;
}

std::unique_ptr<dae::GameObject> Utils::CreateMenuMarker()
{
    auto Marker = Utils::CreateBackgroundObject("MainMenu/Marker.png");
    Marker->GetTransform().SetScale(glm::vec3{2, 2, 2});
    Marker->GetTransform().SetWorldPosition(glm::vec3{512 / 2 - 100, 205, 0});

    auto markerComp = std::make_unique<DigDug::MenuMarker>(Marker.get());
    markerComp->AddPosition(glm::vec3{512 / 2 - 100, 205, 0});
    markerComp->AddPosition(glm::vec3{512 / 2 - 100, 235, 0});
    markerComp->AddPosition(glm::vec3{512 / 2 - 100, 265, 0});
    Marker->AddComponent(std::move(markerComp));

    //  no MenuNavigateSystem

    dae::InputManager::GetInstance().AddCommandBinding(
        SDL_SCANCODE_W,
        std::make_unique<DigDug::MenuNavigateCommand>(Marker.get(), -1),
        dae::InputManager::KeyState::Down
    );
    dae::InputManager::GetInstance().AddCommandBinding(
        SDL_SCANCODE_S,
        std::make_unique<DigDug::MenuNavigateCommand>(Marker.get(), 1),
        dae::InputManager::KeyState::Down
    );
    dae::InputManager::GetInstance().AddCommandBinding(
        SDL_SCANCODE_SPACE,
        std::make_unique<DigDug::ConfirmedCommand>(Marker.get()),
        dae::InputManager::KeyState::Down
    );
    return Marker;
}

std::unique_ptr<dae::GameObject> Utils::CreateHighscoreObject(dae::Scene *scene, int score)
{
    auto font = dae::ResourceManager::GetInstance().LoadFont("Fonts/Emulogic-zrEw.ttf", 18);


    auto scoreTextObj = CreateText("00000", glm::vec3{320, 350, 0});
    auto* scoreTextComp = scoreTextObj->GetComponent<dae::TextComponent>();
    scene->Add(std::move(scoreTextObj));

    std::vector<dae::TextComponent*> letterComps;
    float startX = 200.f;
    for (int i = 0; i < 3; ++i)
    {
        auto letterObj = CreateText(".", glm::vec3{startX + i * 40.f, 350.f, 0});
        letterComps.push_back(letterObj->GetComponent<dae::TextComponent>());

        scene->Add(std::move(letterObj));
    }


    std::vector<dae::GameObject*> arrowPtrs;
    auto arrowUp = CreateBackgroundObject("Sprites/HighScoreScreen/MarkerUp.png");
    arrowUp->GetTransform().SetWorldPosition(glm::vec3{startX, 320.f, 0});
    arrowUp->GetTransform().SetScale(glm::vec3{2, 2, 2});
    arrowPtrs.push_back(arrowUp.get());
    scene->Add(std::move(arrowUp));

    auto arrowDown = CreateBackgroundObject("Sprites/HighScoreScreen/MarkerDown.png");
    arrowDown->GetTransform().SetWorldPosition(glm::vec3{startX, 400.f, 0});
    arrowPtrs.push_back(arrowDown.get());
    arrowDown->GetTransform().SetScale(glm::vec3{2, 2, 2});
    scene->Add(std::move(arrowDown));

    std::vector<dae::TextComponent*> hsComps;
    for (int i = 0; i < 3; ++i)
    {
        auto hsObj = CreateText("--------", glm::vec3{180.f, 200.f + i * 35.f, 0});
        hsComps.push_back(hsObj->GetComponent<dae::TextComponent>());
        scene->Add(std::move(hsObj));
    }


    auto obj = std::make_unique<dae::GameObject>(
        static_cast<int>(DigDug::Layer::UI),
        static_cast<int>(DigDug::GameTag::UI)
    );

    auto hsComp = std::make_unique<DigDug::HighScoreComponent>(
        obj.get(), hsComps, letterComps, arrowPtrs, scoreTextComp
    );
    hsComp->PassScore(score);
    scene->GetEventBus().AddListener(hsComp.get());
    obj->AddComponent(std::move(hsComp));

    dae::InputManager::GetInstance().AddCommandBinding(
    SDL_SCANCODE_W,
    std::make_unique<DigDug::HighScoreNavigatecommand>(obj.get(), -1),
    dae::InputManager::KeyState::Down
);
    dae::InputManager::GetInstance().AddCommandBinding(
        SDL_SCANCODE_S,
        std::make_unique<DigDug::HighScoreNavigatecommand>(obj.get(), 1),
        dae::InputManager::KeyState::Down
    );
    dae::InputManager::GetInstance().AddCommandBinding(
        SDL_SCANCODE_SPACE,
        std::make_unique<DigDug::HighScoreConfirmCommand>(obj.get()),
        dae::InputManager::KeyState::Down
    );


    return obj;
}

std::unique_ptr<dae::GameObject> Utils::CreateLevelManager( std::vector<DigDug::LevelData> levels)
{
    auto obj = std::make_unique<dae::GameObject>();
    auto comp = std::make_unique<DigDug::LevelComponent>(obj.get(), std::move(levels));
    dae::SceneManager::GetInstance().GetActiveScene()->GetEventBus().AddListener(comp.get());
    obj->AddComponent(std::move(comp));
    return obj;
}

std::vector<DigDug::LevelData> Utils::CreateLevelList()
{
    return{
            {
                .tilemapSprites = "Sprites/Blocks.png",
                .tilemapIndex   = "Data/Sprites/Levels/TilePositions/IndexedFile.png",
                .EnemyPooka     = "Data/Sprites/Levels/EnemyPositions/Pooka/EnemyMap.png",
                .EnemyFygar     = "Data/Sprites/Levels/EnemyPositions/Fygar/FygarMap1.png",
                .PlayerPos      = glm::vec3{64.f, 32.f, 0.f},
             },
             {
                 .tilemapSprites = "Sprites/Blocks.png",
                 .tilemapIndex   = "Data/Sprites/Levels/TilePositions/Tiles2.png",
                 .EnemyPooka     = "Data/Sprites/Levels/EnemyPositions/Pooka/PookaMap2.png",
                 .EnemyFygar     = "Data/Sprites/Levels/EnemyPositions/Fygar/FygarMap2.png",
                 .PlayerPos      = glm::vec3{64.f, 32.f, 0.f},
            },
        {
            .tilemapSprites = "Sprites/Blocks.png",
            .tilemapIndex   = "Data/Sprites/Levels/TilePositions/Tiles3.png",
            .EnemyPooka     = "Data/Sprites/Levels/EnemyPositions/Pooka/PookaMap3.png",
            .EnemyFygar     = "Data/Sprites/Levels/EnemyPositions/Fygar/FygarMap3.png",
            .PlayerPos      = glm::vec3{64.f, 32.f, 0.f},
        },
        };
}

bool Utils::IsIntersection(DigDug::TilemapComponent *tilemap, glm::ivec2 currentGrid, glm::vec2 currentDir)
{
    std::vector<glm::vec2> perpendiculars;
    if (currentDir.x != 0)
        perpendiculars = {{ 0,1 }, { 0,-1 }};
    else
        perpendiculars = {{ 1,0 }, { -1,0 }};

    for (auto& p : perpendiculars)
    {
        if (tilemap->isTileOpen(
            currentGrid.x + static_cast<int>(p.x),
            currentGrid.y + static_cast<int>(p.y)))
            return true;
    }
    return false;
}

glm::vec2 Utils::PickBestDirection(DigDug::TilemapComponent *tilemap, dae::GameObject *player, glm::ivec2 fromGrid,
    glm::vec2 currentDir)
{
    auto playerGrid = tilemap->WorldToGrid(player->GetTransform().GetWorldPosition());

    std::vector<glm::vec2> directions = {{ 1,0 }, { -1,0 }, { 0,1 }, { 0,-1 }};

    glm::vec2 bestDir = currentDir;
    int bestDist      = INT_MAX;

    for (auto& d : directions)
    {
        if (d == -currentDir) continue;

        int nx = fromGrid.x + static_cast<int>(d.x);
        int ny = fromGrid.y + static_cast<int>(d.y);
        if (!tilemap->isTileOpen(nx, ny)) continue;

        int dist = std::abs(nx - playerGrid.x) + std::abs(ny - playerGrid.y);
        if (dist < bestDist)
        {
            bestDist = dist;
            bestDir  = d;
        }
    }

    // dead end fallback
    if (bestDist == INT_MAX)
        bestDir = -currentDir;

    return bestDir;
}
