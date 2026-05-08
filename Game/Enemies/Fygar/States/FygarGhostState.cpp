//
// Created by omen on 08/05/2026.
//

#include "FygarGhostState.h"

#include "FygarBehaviour.h"
#include "GameObject.h"
#include "SpriteAnimationComponent.h"


void game::FygarGhostState::Enter(FygarBehaviour &Data)
{
    auto* obj = Data.GetOwner();

    if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
        spriteComp->SetAnimation(0 , 6 , 7);
}

void game::FygarGhostState::Update(FygarBehaviour &, float ) {

}

void game::FygarGhostState::Exit(FygarBehaviour &) {

}
