//
// Created by omen on 08/05/2026.
//

#include "FygarDeadState.h"


#include "SpriteAnimationComponent.h"
#include "FygarBehaviour.h"
#include "GameObject.h"

void DigDug::FygarDeadState::Enter(FygarBehaviour& Data)
{

    auto* obj = Data.GetOwner();

    if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
        spriteComp->SetAnimation(0 , 0 , 1);

}


void DigDug::FygarDeadState::Update(FygarBehaviour &, float )
{

}


void DigDug::FygarDeadState::Exit(FygarBehaviour &) {

}