//
// Created by omen on 06/05/2026.
//

#include "PookaGhostState.h"
#include "PookaNormalState.h"
#include "PookaBehaviour.h"
#include "SpriteAnimationComponent.h"


void DigDug::PookaGhostState::Enter(PookaBehaviour& Data )
{
    m_timer = 0;
    auto* obj = Data.GetOwner();

    if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
        spriteComp->SetAnimation(0 , 3 , 4);

}

void DigDug::PookaGhostState::Update(PookaBehaviour&  , float dt)
{
    m_timer += dt;


}

void DigDug::PookaGhostState::Exit(PookaBehaviour& ) {

}
