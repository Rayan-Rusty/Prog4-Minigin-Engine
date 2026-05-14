//
// Created by omen on 09/05/2026.
//

#include "PlayerIdleState.h"
#include "Player/PlayerBehaviour.h"
#include "GameObject.h"
#include "MovementComponent.h"
#include "SpriteAnimationComponent.h"
#include "MovementComponent.h"
#include "PlayerWalkingState.h"



void DigDug::PlayerIdleState::Enter(PlayerBehaviour &Data)
{
    m_Timer = 0;
    auto* obj = Data.GetOwner();

    if (auto spriteComp = obj->GetComponent<dae::SpriteAnimationComponent>())
        spriteComp->SetAnimation(0 , 0 , 0);
}

void DigDug::PlayerIdleState::Update(PlayerBehaviour& Data, float ) {
    auto* moveComp = Data.GetOwner()->GetComponent<dae::MovementComponent>();

    if (moveComp && moveComp->IsMoving())
    {
        Data.ChangeState(std::make_unique<PlayerWalkingState>());
    }
}

void DigDug::PlayerIdleState::Exit(PlayerBehaviour &)
{

}
