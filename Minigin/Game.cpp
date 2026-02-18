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


dae::Game::Game(dae::Scene& scene)
    :m_Scene(scene)
{

}

void dae::Game::init()
{

    auto go = std::make_unique<dae::GameObject>();
    go->SetTexture("background.png");
    m_Scene.Add(std::move(go));

    go = std::make_unique<dae::GameObject>();
    go->SetTexture("logo.png");
    go->SetPosition(358, 180);
    m_Scene.Add(std::move(go));

    auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
    auto textGO = std::make_unique<dae::GameObject>();
    textGO->GetTransform().SetPosition(292, 20);

    auto textComp = std::make_unique<dae::TextObject>(textGO.get(), "Programming 4 Assignment", font);
    textComp->SetColor({255, 255, 0, 255});
    textGO->AddComponent(std::move(textComp));
    m_Scene.Add(std::move(textGO));


}

void dae::Game::Update(float deltaTime)
{
    m_Scene.Update(deltaTime);

}

void dae::Game::Draw() const
{
    m_Scene.Render();
}
