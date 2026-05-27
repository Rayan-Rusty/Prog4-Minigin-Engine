//
// Created by omen on 08/05/2026.
//

#include "FygarInflatedState.h"

#include "SpriteAnimationComponent.h"
#include "FygarBehaviour.h"
#include "GameObject.h"

void DigDug::FygarInflatedState::Enter(FygarBehaviour& Data)
{

    auto* obj = Data.GetOwner();


    if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
    {
        std::vector<SDL_FRect> InflateFrames =
        {
            {0, 32, 16, 16},
            {16 , 32, 32, 32},
            {32 , 32, 32, 32},
            {48 , 32, 32, 32}
        };

        spriteComp->SetAnimation( InflateFrames, 0.2f , true);
    }

}

std::unique_ptr<State<DigDug::FygarBehaviour>> DigDug::FygarInflatedState::Update(FygarBehaviour &)
{
    return nullptr;
}


void DigDug::FygarInflatedState::Exit(FygarBehaviour &) {

}