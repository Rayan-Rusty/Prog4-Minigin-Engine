//
// Created by omen on 06/05/2026.
//

#include "PookaNormalState.h"


#include "PookaBehaviour.h"
#include "PookaInflatedState.h"
#include "SpriteAnimationComponent.h"



void DigDug::PookaNormalState::Enter(PookaBehaviour& Data )
{
    m_timer = 0;
    auto* obj = Data.GetOwner();

    if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
    {
        std::vector<SDL_FRect> normalState =
        {
            {0, 0, 16, 16},
            {16 , 0, 16, 16}

        };

        spriteComp->SetAnimation( normalState, 0.2f , true);
    }


}

void DigDug::PookaNormalState::Update(PookaBehaviour& Data , float dt)
{
    m_timer += dt;

    // DEMO ONLY
    if (m_timer > 2.0f)
    {
       Data.ChangeState(std::make_unique<PookaInflatedState>());
    }
}

void DigDug::PookaNormalState::Exit(PookaBehaviour& )
{

}
