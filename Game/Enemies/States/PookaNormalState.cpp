//
// Created by omen on 06/05/2026.
//

#include "PookaNormalState.h"

#include "PookaGhostState.h"
#include "../Pooka.h"
#include "Components/RenderComponent.h"


PookaNormalState::~PookaNormalState() {

}

void PookaNormalState::Enter(Pooka& pooka )
{
    m_timer = 0;
    auto* obj = pooka.GetOwner();

    if (auto* render = obj->GetComponent<dae::RenderComponent>())
    {
        render->SetTextureFilePath("Sprites/Pooka.png");
    }
}

void PookaNormalState::Update(Pooka& pooka , float dt)
{
    m_timer += dt;

    // DEMO ONLY
    if (m_timer > 2.0f)
    {
        pooka.ChangeState(std::make_unique<PookaGhostState>());
    }
}

void PookaNormalState::Exit(Pooka& ) {

}
