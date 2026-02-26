//
// Created by omen on 14/02/2026.
//

#include "Game.h"

#include "SceneManager.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "RenderComponent.h"
#include "RotationComponent.h"

dae::Game::Game(dae::Scene &scene)
    : m_Scene(scene) {
}

void dae::Game::init() {
    //init variables
    auto go{std::make_unique<dae::GameObject>()};
    auto RenderComp{std::make_unique<RenderComponent>(go.get())};


    //---------Background-------------
    RenderComp->SetTextureFilePath("background.png");
    go->AddComponent(std::move(RenderComp));
    m_Scene.Add(std::move(go));

    //---------Logo-------------
    go = std::make_unique<dae::GameObject>();
    go->GetTransform().SetLocalPosition(glm::vec3{358, 180,0});
    RenderComp = std::make_unique<RenderComponent>(go.get());

    RenderComp->SetTextureFilePath("logo.png");
    go->AddComponent(std::move(RenderComp));
    m_Scene.Add(std::move(go));


    //---------Texts-------------
    auto font{dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36)};
    auto textGO{std::make_unique<dae::GameObject>()};
    textGO->GetTransform().SetLocalPosition(glm::vec3{292, 20 ,0});

    auto textComp{std::make_unique<dae::TextComponent>(textGO.get(), "Programming 4 Assignment", font)};
    RenderComp = std::make_unique<RenderComponent>(textGO.get());
    textComp->SetColor({255, 255, 255, 255});
    textGO->AddComponent(std::move(RenderComp));
    textGO->AddComponent(std::move(textComp));
    m_Scene.Add(std::move(textGO));

    //fps Counter

    auto FpsGameObject{std::make_unique<dae::GameObject>()};
    FpsGameObject->GetTransform().SetLocalPosition(glm::vec3{10,10,0});

    auto TextComp{std::make_unique<dae::TextComponent>(FpsGameObject.get(), "FPS : 0", font)};
    TextComp->SetColor({255, 255, 255, 255});
    RenderComp = std::make_unique<RenderComponent>(FpsGameObject.get());

    FpsGameObject->AddComponent(std::move(RenderComp));
    FpsGameObject->AddComponent(std::move(TextComp));
    FpsGameObject->AddComponent(std::make_unique<dae::FPSComponent>(FpsGameObject.get()));
    m_Scene.Add(std::move(FpsGameObject));


    //##########################################################
    //                  objects with children
    //##########################################################
    auto parentObject{std::make_unique<dae::GameObject>()};


    parentObject->GetTransform().SetLocalPosition(glm::vec3{250,250,0});

    RenderComp = std::make_unique<RenderComponent>(parentObject.get());
    RenderComp->SetTextureFilePath("Dragon.png");

    auto rotationComponent {std::make_unique<dae::RotationComponent>(parentObject.get(),glm::vec3{270,270,0}, 1.f)};


    parentObject->AddComponent(std::move(rotationComponent));
    parentObject->AddComponent(std::move(RenderComp));

    auto child {std::make_unique<dae::GameObject>()};
    child->GetTransform().SetLocalPosition(glm::vec3{20,20,0});

    child->SetParent(parentObject.get() , false);
    RenderComp= std::make_unique<RenderComponent>(child.get());
    RenderComp->SetTextureFilePath("Player.png");


    rotationComponent = std::make_unique<dae::RotationComponent>(child.get(),glm::vec3{0,0,0}, -1.f);
    child->AddComponent(std::move(rotationComponent));
    child->AddComponent(std::move(RenderComp));

    m_Scene.Add(std::move(parentObject));
    m_Scene.Add(std::move(child));
}

void dae::Game::Update(float deltaTime) {
    //TODO DeltaTime should be a singleton so i dont have to give it in as a parameter in every function
    m_Scene.Update(deltaTime);
}

void dae::Game::Draw() const {
    m_Scene.Render();
}
