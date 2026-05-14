

#include "DigDug.h"

#include "SceneManager.h"
#include "ResourceManager.h"

#include "GameObject.h"
#include "Scene.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "RenderComponent.h"
#include "RotationComponent.h"

#include <algorithm>

#include "InputManager.h"
#include "MoveCommand.h"
#include "MovementComponent.h"
#include "Gamepad.h"
#include "GamepadDataStructs.h"
#include "EventsIds.h"

#include "ServiceLocator.h"
#include "SoundEventListener.h"
#include "DebugSystem.h"
#include "Keyboard.h"
#include "PlayerBehaviour.h"
#include "PookaBehaviour.h"
#include "TilemapComponent.h"
#include "Utils.h"
#include "FygarBehaviour.h"


//TODO ASYNC noise
//TODO remove FPS object
//TODO give in name without keyboard
//TODO SPrites need to be able to be multiple cols or rows


void DigDug::Game::Init()
{
   // InitializeMenuScreen();
   // InitializeGame();
    InitFirstLevel();

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


void DigDug::Game::InitializeGame() {

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
    RenderComp->SetIsUI(true);
    go->AddComponent(std::move(RenderComp));
    scene->Add(std::move(go));

    //---------Logo-------------
    go = std::make_unique<dae::GameObject>();
    go->GetTransform().SetLocalPosition(glm::vec3{358, 180,0});
    RenderComp = std::make_unique<dae::RenderComponent>(go.get());
    RenderComp->SetIsUI(true);

    RenderComp->SetTextureFilePath("logo.png");
    go->AddComponent(std::move(RenderComp));
    scene->Add(std::move(go));


    //---------Texts-------------
    auto font{dae::ResourceManager::GetInstance().LoadFont("Fonts/Emulogic-zrEw.ttf", 11)};
    auto textGO{std::make_unique<dae::GameObject>()};
    textGO->GetTransform().SetLocalPosition(glm::vec3{292, 20 ,0});

    auto textComp{std::make_unique<dae::TextComponent>(textGO.get(), "Programming 4 Assignment", font)};
    RenderComp = std::make_unique<dae::RenderComponent>(textGO.get());
    RenderComp->SetIsUI(true);
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
    RenderComp->SetIsUI(true);
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
    RenderComp->SetIsUI(true);
    auto movementComponent{std::make_unique<dae::MovementComponent>(parentObject.get() , 200.f)};
    parentObject->AddComponent(std::move(movementComponent));
    parentObject->AddComponent(std::move(RenderComp));


    auto SecondPlayerObject{std::make_unique<dae::GameObject>()};
    SecondPlayerObject->GetTransform().SetLocalPosition(glm::vec3{280,250,0});

    auto rotateComp = std::make_unique<dae::RotationComponent>(SecondPlayerObject.get(), 5.f);
    RenderComp = std::make_unique<dae::RenderComponent>(SecondPlayerObject.get());

    RenderComp->SetTextureFilePath("Player.png");
    RenderComp->SetIsUI(true);
    auto movementCompon{std::make_unique<dae::MovementComponent>(SecondPlayerObject.get() , 100.f)};
    SecondPlayerObject->AddComponent(std::move(movementCompon));
    SecondPlayerObject->AddComponent(std::move(RenderComp));
   // SecondPlayerObject->AddComponent(std::move());


    // auto gamepad = std::make_unique<dae::Gamepad>(0);
    // dae::InputManager::GetInstance().AddDevice(std::move(gamepad));

    auto moveLeft = std::make_unique<dae::MoveCommand>(parentObject.get() , glm::vec3{-1,0,0});
    //
    // dae::InputManager::GetInstance().AddCommandBinding(SDL_SCANCODE_A, std::make_unique<dae::MoveCommand>(parentObject.get() , glm::vec3{-1,0,0}));
    // dae::InputManager::GetInstance().AddCommandBinding(SDL_SCANCODE_D,std::make_unique<dae::MoveCommand>(parentObject.get() , glm::vec3{1,0,0}));
    // dae::InputManager::GetInstance().AddCommandBinding(SDL_SCANCODE_W, std::make_unique<dae::MoveCommand>(parentObject.get() , glm::vec3{0,-1,0}));
    // dae::InputManager::GetInstance().AddCommandBinding(SDL_SCANCODE_S, std::make_unique<dae::MoveCommand>(parentObject.get() , glm::vec3{0,1,0}));
    // dae::InputManager::GetInstance().AddCommandBinding(dae::GamepadButton::DPadDown, std::make_unique<dae::MoveCommand>(SecondPlayerObject.get() , glm::vec3{0,1,0}));
    // dae::InputManager::GetInstance().AddCommandBinding(dae::GamepadButton::DPadUp, std::make_unique<dae::MoveCommand>(SecondPlayerObject.get() , glm::vec3{0,-1,0}));
    // dae::InputManager::GetInstance().AddCommandBinding(dae::GamepadButton::DPadLeft, std::make_unique<dae::MoveCommand>(SecondPlayerObject.get() , glm::vec3{-1,0,0}));
    // dae::InputManager::GetInstance().AddCommandBinding(dae::GamepadButton::DPadRight, std::make_unique<dae::MoveCommand>(SecondPlayerObject.get() , glm::vec3{1,0,0}));

    scene->Add(std::move(parentObject));
    scene->Add(std::move(SecondPlayerObject));
    //m_CurrentScene->Add(std::move(child));

    //InputManager::GetInstance().bind

    //##########################################################
    //                  Pooka Enemy
    //##########################################################
    auto pookaGO = std::make_unique<dae::GameObject>();
    pookaGO->GetTransform().SetLocalPosition(glm::vec3{0, 10, 0});

    // Render component
    auto pookaRender = std::make_unique<dae::RenderComponent>(pookaGO.get());
    pookaRender->SetTextureFilePath("Sprites/Pooka.png");
    pookaRender->SetIsUI(true);
    pookaGO->AddComponent(std::move(pookaRender));
    pookaGO->GetTransform().SetLocalPosition(glm::vec3{50, 50, 0});
    // Movement
    auto pookaMovement = std::make_unique<dae::MovementComponent>(pookaGO.get(), 50.f);
    pookaGO->AddComponent(std::move(pookaMovement));


    auto pookaAI = std::make_unique<PookaBehaviour>(pookaGO.get());
    pookaGO->AddComponent(std::move(pookaAI));

    scene->Add(std::move(pookaGO));


}

void DigDug::Game::InitializeIMGUIScene()
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

void DigDug::Game::InitFirstLevel()
{
    auto Scene = &dae::SceneManager::GetInstance().CreateScene();



    auto Pooka = Utils::CreateAnimatedSpriteObject("Sprites/PookaSprites.png", 6 , 7 );
    Pooka->GetTransform().SetWorldPosition(glm::vec3{15, 15,0});
    Pooka->GetTransform().SetScale(glm::vec3{2, 2, 2});
    auto pookaAI = std::make_unique<PookaBehaviour>(Pooka.get());
    Pooka->AddComponent(std::move(pookaAI));



    auto Fygar = Utils::CreateAnimatedSpriteObject("Sprites/FygarSprites.png", 8 , 8);
    Fygar->GetTransform().SetWorldPosition(glm::vec3{60, 15, 0});
    Fygar->GetTransform().SetScale(glm::vec3{2, 2, 2});
    auto FygarAI = std::make_unique<FygarBehaviour>(Fygar.get());
    Fygar->AddComponent(std::move(FygarAI));

    auto player = Utils::CreatePlayerCharacter("Sprites/PlayerSprites.png", 3 , 8);
    player->GetTransform().SetWorldPosition(glm::vec3{90, 15, 0});
    player->GetTransform().SetScale(glm::vec3{2, 2, 2});

    auto PlayerAI = std::make_unique<DigDug::PlayerBehaviour>(player.get());
    player->AddComponent(std::move(PlayerAI));

    auto Background = Utils::CreateBackgroundObject("Sprites/Level1Background.png");
    Background->GetTransform().SetScale(glm::vec3{2, 2, 2});
    Background->GetTransform().SetWorldPosition(glm::vec3{800 / 4, 0, 0});


    auto Tilemap = std::make_unique<dae::GameObject>();
    auto tilemapComp = std::make_unique<TilemapComponent>(Tilemap.get());
    tilemapComp->AddTexture("Sprites/Block.png");
    tilemapComp->LoadFromFile("Data/Sprites/IndexedFile.png");
    Tilemap->AddComponent(std::move(tilemapComp));
    Tilemap->GetTransform().SetScale(glm::vec3{2, 2, 2});
    Tilemap->GetTransform().SetWorldPosition(glm::vec3{800 / 4, 0, 0});


    Scene->Add(std::move(Tilemap));
    Scene->Add(std::move(Pooka));
    Scene->Add(std::move(Fygar));
    Scene->Add(std::move(player));

    //TODO keyboard needs ot be auto added
    dae::InputManager::GetInstance().AddDevice(std::make_unique<dae::Keyboard>());

}
