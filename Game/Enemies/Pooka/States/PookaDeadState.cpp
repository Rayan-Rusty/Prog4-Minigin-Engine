//
// Created by omen on 08/05/2026.
//

#include "PookaDeadState.h"



#include "PookaBehaviour.h"
#include "SpriteAnimationComponent.h"


void DigDug::PookaDeadState::Enter(PookaBehaviour& Data )
{
    m_timer = 0;
    auto* obj = Data.GetOwner();


    if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
    {
        std::vector<SDL_FRect> normalState =
        {
            {0, 16, 16, 16},
            {16 , 16, 16, 16}
        };

        spriteComp->SetAnimation( normalState, 0.2f , true);
    }

}

void DigDug::PookaDeadState::Update(PookaBehaviour&  , float dt)
{
    m_timer += dt;


}

void DigDug::PookaDeadState::Exit(PookaBehaviour& )
{

}
