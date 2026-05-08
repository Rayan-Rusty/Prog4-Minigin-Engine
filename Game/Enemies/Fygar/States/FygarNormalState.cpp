//
// Created by omen on 08/05/2026.
//

#include "FygarNormalState.h"
#include "FygarBehaviour.h"
#include "GameObject.h"
#include "SpriteAnimationComponent.h"

void game::FygarNormalState::Enter(FygarBehaviour &Data)
{
    auto* obj = Data.GetOwner();

    if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
        spriteComp->SetAnimation(0 , 0 , 1);
}

void game::FygarNormalState::Update(FygarBehaviour &, float )
{

}

void game::FygarNormalState::Exit(FygarBehaviour &)
{

}
