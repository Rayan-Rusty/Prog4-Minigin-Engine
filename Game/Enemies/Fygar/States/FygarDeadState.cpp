//
// Created by omen on 08/05/2026.
//

#include "FygarDeadState.h"


#include "SpriteAnimationComponent.h"
#include "FygarBehaviour.h"
#include "GameObject/GameObject.h"

void DigDug::FygarDeadState::Enter(FygarBehaviour& )
{

    // auto* obj = Data.GetOwner();

    // if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
    //     spriteComp->SetAnimation(0 , 0 , 1);

}

std::unique_ptr<State<DigDug::FygarBehaviour>> DigDug::FygarDeadState::Update(float , FygarBehaviour &)
{
    return nullptr;
}


void DigDug::FygarDeadState::Exit(FygarBehaviour &) {

}