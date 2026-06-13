#include "PlayerMoveCommand.h"

#include "EventsIds.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "PlayerMovement.h"

DigDug::PlayerMoveCommand::PlayerMoveCommand(dae::GameObject *actor, const glm::ivec2& direction)
: GameActorCommand(actor), m_Direction(direction)
{
}

void DigDug::PlayerMoveCommand::Execute()
{
    auto* moveComp = GetGameActor()->GetComponent<DigDug::PlayerMovement>();


    if (moveComp)
    {
        moveComp->SetDirection(m_Direction);

        dae::Event e(MOVED);
        e.nbArgs = 3;
        e.args[0].intValue = m_Direction.x;
        e.args[1].intValue = m_Direction.y;
        e.args[2].intValue = (m_Direction.x != 0 || m_Direction.y != 0) ? 1 : 0;

        dae::SceneManager::GetInstance().GetActiveScene()->GetEventBus().QueueEvent(e);
    }
}
