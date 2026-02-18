//
// Created by omen on 14/02/2026.
//

#include "Game.h"

#include "SceneManager.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TextObject.h"
#include "FPSComponent.h"
#include "RenderComponent.h"

dae::Game::Game(dae::Scene& scene)
    :m_Scene(scene)
{

}

void dae::Game::init()
{

    auto go = std::make_unique<dae::GameObject>();
    auto RenderBackground = std::make_unique<RenderComponent>(go.get());

    RenderBackground->SetTextureFile("background.png");
    go->AddComponent(std::move(RenderBackground));
    m_Scene.Add(std::move(go));

    go = std::make_unique<dae::GameObject>();
    go->SetPosition(358, 180);
    RenderBackground =  std::make_unique<RenderComponent>(go.get());

    RenderBackground->SetTextureFile("logo.png");
    go->AddComponent(std::move(RenderBackground));
    m_Scene.Add(std::move(go));





    auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
    auto textGO = std::make_unique<dae::GameObject>();
    textGO->SetPosition(292, 20);

    auto textComp = std::make_unique<dae::TextObject>(textGO.get(), "Programming 4 Assignment", font);
    textComp->SetColor({255, 255, 0, 255});

    textGO->AddComponent(std::move(textComp));
    m_Scene.Add(std::move(textGO));

    //fps Counter
    auto FpsGameObject = std::make_unique<dae::GameObject>();
    FpsGameObject->SetPosition(10, 10);
    auto TextComp = std::make_unique<dae::TextObject>(FpsGameObject.get(), "FPS : 0", font);
    TextComp->SetColor({255, 255, 0, 255});
    TextComp->AddFPSComponent();

    FpsGameObject->AddComponent(std::move(TextComp));



    m_Scene.Add(std::move(FpsGameObject));


}

void dae::Game::Update(float deltaTime)
{
    m_Scene.Update(deltaTime);

}

void dae::Game::Draw() const
{
    m_Scene.Render();
}
