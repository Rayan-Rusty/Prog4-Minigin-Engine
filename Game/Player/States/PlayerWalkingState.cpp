//
// Created by omen on 09/05/2026.
//

#include "PlayerWalkingState.h"

#include "GameObject.h"
#include "MovementComponent.h"
#include "PlayerIdleState.h"
#include "SpriteAnimationComponent.h"
#include "Player/PlayerBehaviour.h"


void DigDug::PlayerWalkingState::Enter(PlayerBehaviour &Data)
{
    m_Timer = 0;
    auto* obj = Data.GetOwner();

    if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
        spriteComp->SetAnimation(0 , 0 , 1);
}

void DigDug::PlayerWalkingState::Update(PlayerBehaviour &Data, float )
{
    auto* moveComp = Data.GetOwner()->GetComponent<dae::MovementComponent>();

    if (moveComp && !moveComp->IsMoving())
    {
        Data.ChangeState(std::make_unique<PlayerIdleState>());

    }
}

void DigDug::PlayerWalkingState::Exit(PlayerBehaviour &) {

}
