//
// Created by omen on 14/02/2026.
//

#include "Game.h"

#include "../Minigin/Managers/SceneManager.h"
#include "../Minigin/Managers/ResourceManager.h"

#include "../Minigin/GameObject.h"
#include "../Minigin/Scene.h"
#include "../Minigin/Components/TextComponent.h"
#include "../Minigin/Components/FPSComponent.h"
#include "../Minigin/Components/RenderComponent.h"
#include "../Minigin/Components/RotationComponent.h"

#include <algorithm>

#include "../Minigin/Managers/InputManager.h"
#include "../Minigin/Commands/MoveCommand.h"
#include "../Minigin/Components/MovementComponent.h"
#include "../Minigin/Gamepad.h"
#include "../Minigin/GamepadDataStructs.h"
#include "../Minigin/EventQueue/EventsIds.h"
#include "../Minigin/Sound/Decorator.h"
#include "../Minigin/Sound/ServiceLocator.h"
#include "../Minigin/Sound/SoundEventListener.h"
#include "../Minigin/Systems/DebugSystem.h"


void game::Game::Init()
{
    InitializeMenuScreen();
    //InitializeGame();
}

void game::Game::Update(float deltaTime)
{
    dae::SceneManager::GetInstance().Update(deltaTime);

}

void game::Game::Draw() const
{
    dae::SceneManager::GetInstance().Render();
}


void game::Game::InitializeMenuScreen()
{
    auto scene = &dae::SceneManager::GetInstance().CreateScene();


    //---------Background-------------
    auto go{std::make_unique<dae::GameObject>()};
    auto RenderComp{std::make_unique<dae::RenderComponent>(go.get())};
    RenderComp->SetTextureFilePath("Sprites/MenuScreen.png");
    go->AddComponent(std::move(RenderComp));
    scene->Add(std::move(go));


    auto FpsGameObject{std::make_unique<dae::GameObject>()};
    FpsGameObject->GetTransform().SetLocalPosition(glm::vec3{10,10,0});
    auto font{dae::ResourceManager::GetInstance().LoadFont("Fonts/Emulogic-zrEw.ttf", 18)};
    auto TextComp{std::make_unique<dae::TextComponent>(FpsGameObject.get(), "FPS : 0", font)};
    TextComp->SetColor({255, 255, 255, 255});
    RenderComp = std::make_unique<dae::RenderComponent>(FpsGameObject.get());

    RenderComp->SetIsUI(true);
    FpsGameObject->AddComponent(std::move(RenderComp));
    FpsGameObject->AddComponent(std::move(TextComp));
    FpsGameObject->AddComponent(std::make_unique<dae::FPSComponent>(FpsGameObject.get()));
    scene->Add(std::move(FpsGameObject));

}


void game::Game::InitializeGame() {

    auto scene = &dae::SceneManager::GetInstance().CreateScene();

    auto& sound = dae::ServiceLocator::get_sound_system();
    sound.load_sound(1, "Data/Sound/pickupCoin.wav");
    auto soundListener = std::make_unique<dae::SoundEventListener>();
    scene->StoreSystem(std::move(soundListener));
    //-------------------------- Event Queues ---------------------------------------


    auto DebugSystem = std::make_unique<dae::DebugSystem>();
    scene->StoreSystem(std::move(DebugSystem));

    dae::Event e(LEVEL_STARTED);
    scene->GetEventBus().QueueEvent(e);

    //-------------------------- Event Queues ---------------------------------------


    //init variables
    auto go{std::make_unique<dae::GameObject>()};
    auto RenderComp{std::make_unique<dae::RenderComponent>(go.get())};


    //---------Background-------------
    RenderComp->SetTextureFilePath("background.png");
    go->AddComponent(std::move(RenderComp));
    scene->Add(std::move(go));

    //---------Logo-------------
    go = std::make_unique<dae::GameObject>();
    go->GetTransform().SetLocalPosition(glm::vec3{358, 180,0});
    RenderComp = std::make_unique<dae::RenderComponent>(go.get());

    RenderComp->SetTextureFilePath("logo.png");
    go->AddComponent(std::move(RenderComp));
    scene->Add(std::move(go));


    //---------Texts-------------
    auto font{dae::ResourceManager::GetInstance().LoadFont("Fonts/Emulogic-zrEw.ttf", 11)};
    auto textGO{std::make_unique<dae::GameObject>()};
    textGO->GetTransform().SetLocalPosition(glm::vec3{292, 20 ,0});

    auto textComp{std::make_unique<dae::TextComponent>(textGO.get(), "Programming 4 Assignment", font)};
    RenderComp = std::make_unique<dae::RenderComponent>(textGO.get());
    textComp->SetColor({255, 255, 255, 255});
    textGO->AddComponent(std::move(RenderComp));
    textGO->AddComponent(std::move(textComp));
    scene->Add(std::move(textGO));

    //fps Counter

    auto FpsGameObject{std::make_unique<dae::GameObject>()};
    FpsGameObject->GetTransform().SetLocalPosition(glm::vec3{10,10,0});

    auto TextComp{std::make_unique<dae::TextComponent>(FpsGameObject.get(), "FPS : 0", font)};
    TextComp->SetColor({255, 255, 255, 255});
    RenderComp = std::make_unique<dae::RenderComponent>(FpsGameObject.get());
    FpsGameObject->AddComponent(std::move(RenderComp));
    FpsGameObject->AddComponent(std::move(TextComp));
    FpsGameObject->AddComponent(std::make_unique<dae::FPSComponent>(FpsGameObject.get()));
    scene->Add(std::move(FpsGameObject));


    //##########################################################
    //                  Moving Objects
    //##########################################################
    auto parentObject{std::make_unique<dae::GameObject>()};


    parentObject->GetTransform().SetLocalPosition(glm::vec3{250,250,0});

    RenderComp = std::make_unique<dae::RenderComponent>(parentObject.get());
    RenderComp->SetTextureFilePath("Dragon.png");
    auto movementComponent{std::make_unique<dae::MovementComponent>(parentObject.get() , 200.f)};
    parentObject->AddComponent(std::move(movementComponent));
    parentObject->AddComponent(std::move(RenderComp));


    auto SecondPlayerObject{std::make_unique<dae::GameObject>()};
    SecondPlayerObject->GetTransform().SetLocalPosition(glm::vec3{280,250,0});

    auto rotateComp = std::make_unique<dae::RotationComponent>(SecondPlayerObject.get(), 5.f);
    RenderComp = std::make_unique<dae::RenderComponent>(SecondPlayerObject.get());

    RenderComp->SetTextureFilePath("Player.png");

    auto movementCompon{std::make_unique<dae::MovementComponent>(SecondPlayerObject.get() , 100.f)};
    SecondPlayerObject->AddComponent(std::move(movementCompon));
    SecondPlayerObject->AddComponent(std::move(RenderComp));
   // SecondPlayerObject->AddComponent(std::move());

    auto hintGO{ std::make_unique<dae::GameObject>() };
    hintGO->GetTransform().SetLocalPosition(glm::vec3{ 292, 80, 0 });

    auto hintText{ std::make_unique<dae::TextComponent>(
        hintGO.get(),
        "Move around to make noise",
        font
    ) };

    auto hintRender{ std::make_unique<dae::RenderComponent>(hintGO.get()) };
    hintText->SetColor({ 255, 255, 0, 255 }); // yellow so it's visible

    hintGO->AddComponent(std::move(hintRender));
    hintGO->AddComponent(std::move(hintText));

    scene->Add(std::move(hintGO));

    // auto gamepad = std::make_unique<dae::Gamepad>(0);
    // dae::InputManager::GetInstance().AddDevice(std::move(gamepad));

    auto moveLeft = std::make_unique<dae::MoveCommand>(parentObject.get() , glm::vec3{-1,0,0});

    dae::InputManager::GetInstance().AddCommandBinding(SDL_SCANCODE_A, std::make_unique<dae::MoveCommand>(parentObject.get() , glm::vec3{-1,0,0}));
    dae::InputManager::GetInstance().AddCommandBinding(SDL_SCANCODE_D,std::make_unique<dae::MoveCommand>(parentObject.get() , glm::vec3{1,0,0}));
    dae::InputManager::GetInstance().AddCommandBinding(SDL_SCANCODE_W, std::make_unique<dae::MoveCommand>(parentObject.get() , glm::vec3{0,-1,0}));
    dae::InputManager::GetInstance().AddCommandBinding(SDL_SCANCODE_S, std::make_unique<dae::MoveCommand>(parentObject.get() , glm::vec3{0,1,0}));
    dae::InputManager::GetInstance().AddCommandBinding(dae::GamepadButton::DPadDown, std::make_unique<dae::MoveCommand>(SecondPlayerObject.get() , glm::vec3{0,1,0}));
    dae::InputManager::GetInstance().AddCommandBinding(dae::GamepadButton::DPadUp, std::make_unique<dae::MoveCommand>(SecondPlayerObject.get() , glm::vec3{0,-1,0}));
    dae::InputManager::GetInstance().AddCommandBinding(dae::GamepadButton::DPadLeft, std::make_unique<dae::MoveCommand>(SecondPlayerObject.get() , glm::vec3{-1,0,0}));
    dae::InputManager::GetInstance().AddCommandBinding(dae::GamepadButton::DPadRight, std::make_unique<dae::MoveCommand>(SecondPlayerObject.get() , glm::vec3{1,0,0}));

    scene->Add(std::move(parentObject));
    scene->Add(std::move(SecondPlayerObject));
    //m_CurrentScene->Add(std::move(child));

    //InputManager::GetInstance().bind
}

void game::Game::InitializeIMGUIScene()
{
    auto scene = &dae::SceneManager::GetInstance().CreateScene();
    auto go{std::make_unique<dae::GameObject>()};
    auto RenderComp{std::make_unique<dae::RenderComponent>(go.get())};


    //---------Background-------------
    RenderComp->SetTextureFilePath("background.png");
    go->AddComponent(std::move(RenderComp));
    scene->Add(std::move(go));

    //---------Logo-------------
    go = std::make_unique<dae::GameObject>();
    go->GetTransform().SetLocalPosition(glm::vec3{358, 180,0});
    RenderComp = std::make_unique<dae::RenderComponent>(go.get());

    RenderComp->SetTextureFilePath("logo.png");
    go->AddComponent(std::move(RenderComp));
    scene->Add(std::move(go));









}