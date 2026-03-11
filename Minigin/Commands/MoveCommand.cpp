//
// Created by omen on 11/03/2026.
//

#include "MoveCommand.h"
#include "Components/MovementComponent.h"

dae::MoveCommand::MoveCommand(GameObject *actor , glm::vec3 direction)
    : GameActorCommand(actor), m_direction(direction)
{

}


void dae::MoveCommand::Execute()
{
    auto moveComp = GetGameActor()->GetComponent<MovementComponent>();
    if (moveComp)
        moveComp->Move(m_direction);
}
