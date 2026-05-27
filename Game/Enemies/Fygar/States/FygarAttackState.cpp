//
// Created by omen on 08/05/2026.
//

#include "FygarAttackState.h"

#include "SpriteAnimationComponent.h"
#include "FygarBehaviour.h"
#include "GameObject.h"

void DigDug::FygarAttackState::Enter(FygarBehaviour& Data)
{

    auto* obj = Data.GetOwner();

    if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
    {
        std::vector<SDL_FRect> AttackFrames =
        {
            {48, 16, 16, 16},
            {64 , 16, 16, 16},
            {80 , 16, 16, 16}
        };

        spriteComp->SetAnimation( AttackFrames, 0.2f , true);
    }


}

std::unique_ptr<State<DigDug::FygarBehaviour>> DigDug::FygarAttackState::Update(FygarBehaviour &)
{
    return nullptr;
}





void DigDug::FygarAttackState::Exit(FygarBehaviour &) {

}
