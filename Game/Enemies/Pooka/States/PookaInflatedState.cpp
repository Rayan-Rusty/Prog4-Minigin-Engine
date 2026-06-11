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
    {
        std::vector<SDL_FRect> InflateFrames =
        {
            {0, 32, 16, 16},
            {16 , 32, 32, 32},
            {48 , 32, 32, 32},
            {80 , 32, 32, 32}
        };

        spriteComp->SetAnimation( InflateFrames, 0.2f , true);
    }


}

std::unique_ptr<State<DigDug::PookaBehaviour>> DigDug::PookaInflatedState::Update(float , PookaBehaviour &)
{
    return nullptr;
}
void DigDug::PookaInflatedState::Exit(PookaBehaviour& ) {

}