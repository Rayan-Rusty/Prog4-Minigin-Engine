//
// Created by omen on 08/05/2026.
//

#include "FygarNormalState.h"
#include "FygarBehaviour.h"
#include "GameObject.h"
#include "SpriteAnimationComponent.h"

void DigDug::FygarNormalState::Enter(FygarBehaviour &Data)
{
    auto* obj = Data.GetOwner();

    if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
        spriteComp->SetAnimation(0 , 0 , 1);
}

void DigDug::FygarNormalState::Update(FygarBehaviour &, float )
{

}

void DigDug::FygarNormalState::Exit(FygarBehaviour &)
{

}
