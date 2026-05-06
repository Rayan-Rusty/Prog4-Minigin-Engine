//
// Created by omen on 06/05/2026.
//

#include "PookaGhostState.h"

#include "PookaNormalState.h"
#include "../Pooka.h"
#include "Components/RenderComponent.h"

PookaGhostState::~PookaGhostState() {

}

void PookaGhostState::Enter(Pooka& pooka )
{
    m_timer = 0;
    auto* obj = pooka.GetOwner();

    if (auto* render = obj->GetComponent<dae::RenderComponent>())
    {
        render->SetTextureFilePath("Sprites/Pookaghost.png");
    }
}

void PookaGhostState::Update(Pooka& pooka , float dt)
{
    m_timer += dt;

    if (m_timer >= m_duration)
    {
        pooka.ChangeState(std::make_unique<PookaNormalState>());
    }
}

void PookaGhostState::Exit(Pooka& ) {

}
