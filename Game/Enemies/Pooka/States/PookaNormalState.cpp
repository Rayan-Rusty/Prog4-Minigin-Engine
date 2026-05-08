//
// Created by omen on 06/05/2026.
//

#include "PookaNormalState.h"

#include "PookaGhostState.h"
#include "PookaBehaviour.h"
#include "SpriteAnimationComponent.h"


PookaNormalState::~PookaNormalState() {

}

void PookaNormalState::Enter(PookaBehaviour& pooka )
{
    m_timer = 0;
    auto* obj = pooka.GetOwner();

    if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
        spriteComp->SetAnimation(0 , 0 , 1);


}

void PookaNormalState::Update(PookaBehaviour& , float dt)
{
    m_timer += dt;

    // DEMO ONLY
    // if (m_timer > 2.0f)
    // {
    //     pooka.ChangeState(std::make_unique<PookaGhostState>());
    // }
}

void PookaNormalState::Exit(PookaBehaviour& )
{

}
