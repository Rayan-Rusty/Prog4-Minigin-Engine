//
// Created by omen on 05/05/2026.
//

#include "Utils.h"

#include "InputManager.h"
#include "Keyboard.h"
#include "MoveCommand.h"
#include "MovementComponent.h"
#include "PlayerBehaviour.h"
#include "Components/RenderComponent.h"
#include "SpriteAnimationComponent.h"
#include "CollisionComponent.h"
#include "CollisionManager.h"
#include "FygarBehaviour.h"
#include "PookaBehaviour.h"
#include "Layers/GameLayers.h"
#include "TilemapComponent.h"
std::unique_ptr<dae::GameObject> Utils::CreateAnimatedSpriteObject(const std::string &TexturePath, int rows, int cols, int layer, int tag )
{
    auto obj = std::make_unique<dae::GameObject>(layer , tag);

    auto renderComp = std::make_unique<dae::RenderComponent>(obj.get());
    renderComp->SetTextureFilePath(TexturePath);

    obj->AddComponent(std::move(renderComp));

    obj->AddComponent(std::make_unique<dae::SpriteAnimationComponent>( obj.get(), rows , cols ));




    return obj;
}

std::unique_ptr<dae::GameObject> Utils::CreatePlayerCharacter(const std::string &TexturePath, int rows, int cols)
{

    auto obj = std::make_unique<dae::GameObject>(static_cast<int>(DigDug::Layer::Foreground), static_cast<int>(DigDug::GameTag::Player));


    //Renderer
    auto renderComp = std::make_unique<dae::RenderComponent>(obj.get());
    renderComp->SetTextureFilePath(TexturePath);

    obj->AddComponent(std::move(renderComp));
    //Sprites
    obj->AddComponent(std::make_unique<dae::SpriteAnimationComponent>( obj.get(), rows , cols ));


    //Movement
    auto movementCompon{std::make_unique<dae::MovementComponent>(obj.get() , 300.f)};
    obj->AddComponent(std::move(movementCompon));

    //Commands
    auto moveLeft = std::make_unique<dae::MoveCommand>(obj.get() , glm::vec3{-1,0,0});

    dae::InputManager::GetInstance().AddCommandBinding(
        SDL_SCANCODE_A,
        std::make_unique<dae::MoveCommand>(obj.get(), glm::vec3{-1,0,0}),
        dae::InputManager::KeyState::Held
    );

    dae::InputManager::GetInstance().AddCommandBinding(
        SDL_SCANCODE_D,
        std::make_unique<dae::MoveCommand>(obj.get(), glm::vec3{1,0,0}),
        dae::InputManager::KeyState::Held
    );

    dae::InputManager::GetInstance().AddCommandBinding(
        SDL_SCANCODE_W,
        std::make_unique<dae::MoveCommand>(obj.get(), glm::vec3{0,-1,0}),
        dae::InputManager::KeyState::Held
    );

    dae::InputManager::GetInstance().AddCommandBinding(
        SDL_SCANCODE_S,
        std::make_unique<dae::MoveCommand>(obj.get(), glm::vec3{0,1,0}),
        dae::InputManager::KeyState::Held
    );
    dae::InputManager::GetInstance().AddCommandBinding(
        dae::GamepadButton::DPadDown,
        std::make_unique<dae::MoveCommand>(obj.get(), glm::vec3{0,1,0}),
        dae::InputManager::KeyState::Held
    );

    dae::InputManager::GetInstance().AddCommandBinding(
        dae::GamepadButton::DPadUp,
        std::make_unique<dae::MoveCommand>(obj.get(), glm::vec3{0,-1,0}),
        dae::InputManager::KeyState::Held
    );

    dae::InputManager::GetInstance().AddCommandBinding(
        dae::GamepadButton::DPadLeft,
        std::make_unique<dae::MoveCommand>(obj.get(), glm::vec3{-1,0,0}),
        dae::InputManager::KeyState::Held
    );

    dae::InputManager::GetInstance().AddCommandBinding(
        dae::GamepadButton::DPadRight,
        std::make_unique<dae::MoveCommand>(obj.get(), glm::vec3{1,0,0}),
        dae::InputManager::KeyState::Held
    );

    return obj;
}


std::unique_ptr<dae::GameObject> Utils::CreateBackgroundObject(const std::string &TexturePath)
{
    auto obj = std::make_unique<dae::GameObject>();

    auto renderComp = std::make_unique<dae::RenderComponent>(obj.get());
    renderComp->SetTextureFilePath(TexturePath);

    obj->AddComponent(std::move(renderComp));



    return obj;
}

std::unique_ptr<dae::GameObject> Utils::CreateFygar()
{
    auto fygar {Utils::CreateEnemy("Sprites/FygarSprites.png" ,8 , 8)};
    fygar->GetTransform().SetScale(glm::vec3{2, 2, 2});
    auto fygarAI = std::make_unique<DigDug::FygarBehaviour>(fygar.get());
    fygar->AddComponent(std::move(fygarAI));

    return fygar;
}

std::unique_ptr<dae::GameObject> Utils::CreatePooka()
{

    auto pooka {Utils::CreateEnemy("Sprites/PookaSprites.png" ,6 , 7 )};
    pooka->GetTransform().SetScale(glm::vec3{2, 2, 2});
    auto pookaAI = std::make_unique<DigDug::PookaBehaviour>(pooka.get());
    pooka->AddComponent(std::move(pookaAI));

    return pooka;

}

std::unique_ptr<dae::GameObject> Utils::CreatePlayer()
{
    auto player = Utils::CreatePlayerCharacter("Sprites/PlayerSprites.png", 3 , 8);
    player->GetTransform().SetWorldPosition(glm::vec3{90, 15, 0});
    player->GetTransform().SetScale(glm::vec3{2, 2, 2});

    auto PlayerAI = std::make_unique<DigDug::PlayerBehaviour>(player.get());
    player->AddComponent(std::move(PlayerAI));
    auto playerCol = std::make_unique<dae::CollisionComponent>(player.get());
    player->AddComponent(std::move(playerCol));
    CollisionManager::GetInstance().Register(player->GetComponent<dae::CollisionComponent>());
    return player;
}

std::unique_ptr<dae::GameObject> Utils::CreateEnemy(const std::string& TexturePath, int rows, int cols)
{
    auto obj = CreateAnimatedSpriteObject(TexturePath, rows, cols, static_cast<int>(DigDug::Layer::Foreground),static_cast<int>(DigDug::GameTag::Enemy));

    auto col = std::make_unique<dae::CollisionComponent>(obj.get());
    obj->AddComponent(std::move(col));
    CollisionManager::GetInstance().Register(obj->GetComponent<dae::CollisionComponent>());

    return obj;
}
std::unique_ptr<dae::GameObject> Utils::CreateTilemap(const std::string& texturePath, const std::string& dataPath)
{
    auto obj = std::make_unique<dae::GameObject>(static_cast<int>(DigDug::Layer::Background), static_cast<int>(DigDug::GameTag::Tilemap));


    auto col = std::make_unique<dae::CollisionComponent>(obj.get());
    obj->AddComponent(std::move(col));

    auto tilemapComp = std::make_unique<DigDug::TilemapComponent>(obj.get());
    obj->GetTransform().SetScale(glm::vec3{2, 2, 2});
    tilemapComp->AddTexture(texturePath);
    tilemapComp->LoadFromFile(dataPath);

    obj->AddComponent(std::move(tilemapComp));

    CollisionManager::GetInstance().Register(obj->GetComponent<dae::CollisionComponent>());

    return obj;
}