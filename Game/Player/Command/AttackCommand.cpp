#include "AttackCommand.h"
#include "GameObject.h"
#include "PlayerAttackState.h"
#include "PlayerBehaviour.h"

namespace DigDug {
    AttackCommand::AttackCommand(dae::GameObject *actor)
        :GameActorCommand(actor)
    {

    }

    void AttackCommand::Execute()
    {
        if (auto* behaviour = GetGameActor()->GetComponent<PlayerBehaviour>())
            behaviour->ChangeState(std::make_unique<PlayerAttackState>());
    }
} // DigDug