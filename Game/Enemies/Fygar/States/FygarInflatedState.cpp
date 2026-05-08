//
// Created by omen on 08/05/2026.
//

#include "FygarInflatedState.h"

#include "SpriteAnimationComponent.h"
#include "FygarBehaviour.h"
#include "GameObject.h"

void game::FygarInflatedState::Enter(FygarBehaviour& Data)
{

    auto* obj = Data.GetOwner();

    if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
        spriteComp->SetAnimation(0 , 0 , 1);

}


void game::FygarInflatedState::Update(FygarBehaviour &, float )
{

}


void game::FygarInflatedState::Exit(FygarBehaviour &) {

}