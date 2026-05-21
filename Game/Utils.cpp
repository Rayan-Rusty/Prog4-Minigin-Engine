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


std::unique_ptr<dae::GameObject> Utils::CreateAnimatedSpriteObject(const std::string &TexturePath, int rows, int cols)
{
    auto obj = std::make_unique<dae::GameObject>();

    auto renderComp = std::make_unique<dae::RenderComponent>(obj.get());
    renderComp->SetTextureFilePath(TexturePath);

    obj->AddComponent(std::move(renderComp));

    obj->AddComponent(std::make_unique<dae::SpriteAnimationComponent>( obj.get(), rows , cols ));




    return obj;
}

std::unique_ptr<dae::GameObject> Utils::CreatePlayerCharacter(const std::string &TexturePath, int rows, int cols)
{

    auto obj = std::make_unique<dae::GameObject>();


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
