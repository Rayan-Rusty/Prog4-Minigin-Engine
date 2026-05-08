//
// Created by omen on 06/05/2026.
//

#include "PookaGhostState.h"
#include "PookaNormalState.h"
#include "PookaBehaviour.h"
#include "SpriteAnimationComponent.h"

PookaGhostState::~PookaGhostState() {

}

void PookaGhostState::Enter(PookaBehaviour& pooka )
{
    m_timer = 0;
    auto* obj = pooka.GetOwner();

    if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
        spriteComp->SetAnimation(0 , 3 , 4);

}

void PookaGhostState::Update(PookaBehaviour& pooka , float dt)
{
    m_timer += dt;

    if (m_timer >= m_duration)
    {
        pooka.ChangeState(std::make_unique<PookaNormalState>());
    }
}

void PookaGhostState::Exit(PookaBehaviour& ) {

}
