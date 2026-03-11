//
// Created by omen on 14/02/2026.
//

#include "Game.h"

#include "SceneManager.h"
#include "ResourceManager.h"

#include "GameObject.h"
#include "Scene.h"
#include "Components/TextComponent.h"
#include "Components/FPSComponent.h"
#include "Components/RenderComponent.h"
#include "Components/RotationComponent.h"

#include <algorithm>

#include "InputManager.h"
#include "Commands/MoveCommand.h"
#include "Components/MovementComponent.h"
#include "Gamepad.h"
#include <Xinput.h>

dae::Game::Game(dae::Scene* scene)
    : m_CurrentScene(scene) {
}

void dae::Game::init()
{
    InitializeGame();
}

void dae::Game::Update(float deltaTime)
{

    m_CurrentScene->Update(deltaTime);
}

void dae::Game::Draw()
{
    m_CurrentScene->Render();

}




void dae::Game::InitializeGame() {

    //init variables
    auto go{std::make_unique<dae::GameObject>()};
    auto RenderComp{std::make_unique<RenderComponent>(go.get())};


    //---------Background-------------
    RenderComp->SetTextureFilePath("background.png");
    go->AddComponent(std::move(RenderComp));
    m_CurrentScene->Add(std::move(go));

    //---------Logo-------------
    go = std::make_unique<dae::GameObject>();
    go->GetTransform().SetLocalPosition(glm::vec3{358, 180,0});
    RenderComp = std::make_unique<RenderComponent>(go.get());

    RenderComp->SetTextureFilePath("logo.png");
    go->AddComponent(std::move(RenderComp));
    m_CurrentScene->Add(std::move(go));


    //---------Texts-------------
    auto font{dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36)};
    auto textGO{std::make_unique<dae::GameObject>()};
    textGO->GetTransform().SetLocalPosition(glm::vec3{292, 20 ,0});

    auto textComp{std::make_unique<dae::TextComponent>(textGO.get(), "Programming 4 Assignment", font)};
    RenderComp = std::make_unique<RenderComponent>(textGO.get());
    textComp->SetColor({255, 255, 255, 255});
    textGO->AddComponent(std::move(RenderComp));
    textGO->AddComponent(std::move(textComp));
    m_CurrentScene->Add(std::move(textGO));

    //fps Counter

    auto FpsGameObject{std::make_unique<dae::GameObject>()};
    FpsGameObject->GetTransform().SetLocalPosition(glm::vec3{10,10,0});

    auto TextComp{std::make_unique<dae::TextComponent>(FpsGameObject.get(), "FPS : 0", font)};
    TextComp->SetColor({255, 255, 255, 255});
    RenderComp = std::make_unique<RenderComponent>(FpsGameObject.get());

    FpsGameObject->AddComponent(std::move(RenderComp));
    FpsGameObject->AddComponent(std::move(TextComp));
    FpsGameObject->AddComponent(std::make_unique<dae::FPSComponent>(FpsGameObject.get()));
    m_CurrentScene->Add(std::move(FpsGameObject));


    //##########################################################
    //                  Moving Objects
    //##########################################################
    auto parentObject{std::make_unique<dae::GameObject>()};


    parentObject->GetTransform().SetLocalPosition(glm::vec3{250,250,0});

    RenderComp = std::make_unique<RenderComponent>(parentObject.get());
    RenderComp->SetTextureFilePath("Dragon.png");
    auto movementComponent{std::make_unique<dae::MovementComponent>(parentObject.get() , 50.f)};
    parentObject->AddComponent(std::move(movementComponent));
    parentObject->AddComponent(std::move(RenderComp));


    auto SecondPlayerObject{std::make_unique<dae::GameObject>()};
    SecondPlayerObject->GetTransform().SetLocalPosition(glm::vec3{280,250,0});
    RenderComp = std::make_unique<RenderComponent>(SecondPlayerObject.get());
    RenderComp->SetTextureFilePath("Player.png");
    auto movementCompon{std::make_unique<dae::MovementComponent>(SecondPlayerObject.get() , 100.f)};
    SecondPlayerObject->AddComponent(std::move(movementCompon));
    SecondPlayerObject->AddComponent(std::move(RenderComp));



    auto gamepad = std::make_unique<dae::Gamepad>(0);
    dae::InputManager::GetInstance().AddDevice(std::move(gamepad));

    auto moveLeft = std::make_unique<dae::MoveCommand>(parentObject.get() , glm::vec3{-1,0,0});

    InputManager::GetInstance().AddCommandBinding(SDL_SCANCODE_A, std::make_unique<dae::MoveCommand>(parentObject.get() , glm::vec3{-1,0,0}));
    InputManager::GetInstance().AddCommandBinding(SDL_SCANCODE_D,std::make_unique<dae::MoveCommand>(parentObject.get() , glm::vec3{1,0,0}));
    InputManager::GetInstance().AddCommandBinding(SDL_SCANCODE_W, std::make_unique<dae::MoveCommand>(parentObject.get() , glm::vec3{0,1,0}));
    InputManager::GetInstance().AddCommandBinding(SDL_SCANCODE_S, std::make_unique<dae::MoveCommand>(parentObject.get() , glm::vec3{0,-1,0}));
    InputManager::GetInstance().AddCommandBinding(XINPUT_GAMEPAD_DPAD_DOWN, std::make_unique<dae::MoveCommand>(SecondPlayerObject.get() , glm::vec3{0,1,0}));
    InputManager::GetInstance().AddCommandBinding(XINPUT_GAMEPAD_DPAD_UP, std::make_unique<dae::MoveCommand>(SecondPlayerObject.get() , glm::vec3{0,-1,0}));
    InputManager::GetInstance().AddCommandBinding(XINPUT_GAMEPAD_DPAD_LEFT, std::make_unique<dae::MoveCommand>(SecondPlayerObject.get() , glm::vec3{-1,0,0}));
    InputManager::GetInstance().AddCommandBinding(XINPUT_GAMEPAD_DPAD_RIGHT, std::make_unique<dae::MoveCommand>(SecondPlayerObject.get() , glm::vec3{1,0,0}));

    m_CurrentScene->Add(std::move(parentObject));
    m_CurrentScene->Add(std::move(SecondPlayerObject));
    //m_CurrentScene->Add(std::move(child));

    //InputManager::GetInstance().bind
}

void dae::Game::InitializeIMGUIScene()
{
    auto go{std::make_unique<dae::GameObject>()};
    auto RenderComp{std::make_unique<RenderComponent>(go.get())};


    //---------Background-------------
    RenderComp->SetTextureFilePath("background.png");
    go->AddComponent(std::move(RenderComp));
    m_CurrentScene->Add(std::move(go));

    //---------Logo-------------
    go = std::make_unique<dae::GameObject>();
    go->GetTransform().SetLocalPosition(glm::vec3{358, 180,0});
    RenderComp = std::make_unique<RenderComponent>(go.get());

    RenderComp->SetTextureFilePath("logo.png");
    go->AddComponent(std::move(RenderComp));
    m_CurrentScene->Add(std::move(go));







}
