//
// Created by omen on 08/05/2026.
//

#include "PookaInflatedState.h"


#include "PookaBehaviour.h"
#include "SpriteAnimationComponent.h"


void DigDug::PookaInflatedState::Enter(PookaBehaviour& Data )
{
    m_timer = 0;
    auto* obj = Data.GetOwner();

    if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
        spriteComp->SetAnimation(0 , 3 , 4);

}

void DigDug::PookaInflatedState::Update(PookaBehaviour&  , float dt)
{
    m_timer += dt;


}

void DigDug::PookaInflatedState::Exit(PookaBehaviour& ) {

}