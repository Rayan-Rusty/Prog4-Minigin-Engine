//
// Created by omen on 08/05/2026.
//

#include "FygarGhostState.h"

#include "FygarBehaviour.h"
#include "../../../../Minigin/GameObject/GameObject.h"
#include "SpriteAnimationComponent.h"


void DigDug::FygarGhostState::Enter(FygarBehaviour &Data)
{
    auto* obj = Data.GetOwner();


    if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
    {
        std::vector<SDL_FRect> ghostFrames =
        {
            {96, 0, 16, 16},
            {112 , 0 , 16, 16}
        };

        spriteComp->SetAnimation( ghostFrames, 0.2f , true);
    }

}

void DigDug::FygarGhostState::Update(FygarBehaviour &, float ) {

}

void DigDug::FygarGhostState::Exit(FygarBehaviour &) {

}
