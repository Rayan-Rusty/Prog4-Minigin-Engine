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
    {
        std::vector<SDL_FRect> normalState =
        {
            {0, 0, 16, 16},
            {16 , 0, 16, 16},
            {32 , 0, 16, 16},
        };

        spriteComp->SetAnimation( normalState, 0.2f , true);
    }
}

std::unique_ptr<State<DigDug::FygarBehaviour>> DigDug::FygarNormalState::Update(float , FygarBehaviour &)
{
    return nullptr;
}

void DigDug::FygarNormalState::Exit(FygarBehaviour &)
{

}

std::type_index DigDug::FygarNormalState::GetType() const
{
    return std::type_index(typeid(FygarNormalState));
}
