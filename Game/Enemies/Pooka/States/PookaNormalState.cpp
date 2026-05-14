//
// Created by omen on 06/05/2026.
//

#include "PookaNormalState.h"

#include "PookaGhostState.h"
#include "PookaBehaviour.h"
#include "SpriteAnimationComponent.h"



void DigDug::PookaNormalState::Enter(PookaBehaviour& Data )
{
    m_timer = 0;
    auto* obj = Data.GetOwner();

    if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
        spriteComp->SetAnimation(0 , 0 , 1);


}

void DigDug::PookaNormalState::Update(PookaBehaviour& Data , float dt)
{
    m_timer += dt;

    // DEMO ONLY
    if (m_timer > 2.0f)
    {
       Data.ChangeState(std::make_unique<PookaGhostState>());
    }
}

void DigDug::PookaNormalState::Exit(PookaBehaviour& )
{

}
