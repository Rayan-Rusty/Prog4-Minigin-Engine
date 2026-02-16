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
    auto to = std::make_unique<dae::TextObject>("Programming 4 Assignment", font);
    to->SetColor({ 255, 255, 0, 255 });
    to->SetPosition(292, 20);
    m_Scene.Add(std::move(to));

    auto fpsText = std::make_unique<dae::TextObject>("FPS: 0", font);
    fpsText->SetPosition(10, 10);
    fpsText->SetColor({ 255, 255, 0, 255 });
    fpsText->SetFPSComponent();
    m_Scene.Add(std::move(fpsText));
}

void dae::Game::Update(float deltaTime)
{
    m_Scene.Update(deltaTime);

}

void dae::Game::Draw() const
{
    m_Scene.Render();
}
