#include "HighScoreNavigatecommand.h"

#include "EventsIds.h"
#include "GameObject.h"
#include "SceneManager.h"


DigDug::HighScoreNavigatecommand::HighScoreNavigatecommand(dae::GameObject *gameObject, int direction)
: GameActorCommand(gameObject)
, m_direction(direction)
{
}

void DigDug::HighScoreNavigatecommand::Execute()
{
    dae::Event e{ m_direction > 0 ? PressedForwardArrow : PressedPreviousArrow };
    dae::SceneManager::GetInstance().GetActiveScene()->GetEventBus().QueueEvent(e);
}
