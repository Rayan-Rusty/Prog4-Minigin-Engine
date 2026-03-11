//
// Created by omen on 11/03/2026.
//

#include "MoveLeftCommand.h"
#include "Components/MovementComponent.h"

dae::MoveLeftCommand::MoveLeftCommand(GameObject *actor)
    : GameActorCommand(actor)
{

}


void dae::MoveLeftCommand::Execute()
{
    auto moveComp = GetGameActor()->GetComponent<MovementComponent>();
    if (moveComp)
        moveComp->Move({-1, 0, 0});
}
