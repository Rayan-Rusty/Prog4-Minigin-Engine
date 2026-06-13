//
// Created by omen on 09/05/2026.
//

#include "PlayerIdleState.h"
#include "PlayerBehaviour.h"
#include "GameObject.h"
#include "MovementComponent.h"
#include "SpriteAnimationComponent.h"

#include "PlayerWalkingState.h"



void DigDug::PlayerIdleState::Enter(PlayerBehaviour &Data)
{
    m_Timer = 0;
    auto* obj = Data.GetOwner();

    if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
    {
        std::vector<SDL_FRect> idle =
        {
            {0, 0, 16, 16},
        };

        spriteComp->SetAnimation( idle, 0.2f , false);
    }

    
}

//TODO State update is a return ?
std::unique_ptr<State<DigDug::PlayerBehaviour>> DigDug::PlayerIdleState::Update(float , PlayerBehaviour& Data)
{

    if (Data.GetIsMoving())
    {

        return std::make_unique<PlayerWalkingState>();
    }

    return nullptr;

}

void DigDug::PlayerIdleState::Exit(PlayerBehaviour &)
{

}

std::type_index DigDug::PlayerIdleState::GetType() const
{
    return std::type_index(typeid(PlayerIdleState));
}
