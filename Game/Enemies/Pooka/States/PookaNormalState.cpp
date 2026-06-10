//
// Created by omen on 06/05/2026.
//

#include "PookaNormalState.h"


#include "CollisionComponent.h"
#include "PookaBehaviour.h"
#include "PookaInflatedState.h"
#include "SpriteAnimationComponent.h"



void DigDug::PookaNormalState::Enter(PookaBehaviour& Data )
{
    m_timer = 0;
    auto* obj = Data.GetOwner();

    auto* col = obj->GetComponent<dae::CollisionComponent>();
    if (col) col->SetEnabled(true);

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

std::unique_ptr<State<DigDug::PookaBehaviour>> DigDug::PookaNormalState::Update(PookaBehaviour &)
{
    return nullptr;
}


void DigDug::PookaNormalState::Exit(PookaBehaviour& )
{

}
