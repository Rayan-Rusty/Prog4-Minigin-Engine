#include "HighScoreConfirmCommand.h"

#include "EventsIds.h"
#include "GameActorCommand.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"

DigDug::HighScoreConfirmCommand::HighScoreConfirmCommand(dae::GameObject* gameObject)
    : dae::GameActorCommand(gameObject)
{}

void DigDug::HighScoreConfirmCommand::Execute()
{
    dae::Event e{ OnConfirmPressed };
    dae::SceneManager::GetInstance().GetActiveScene()->GetEventBus().QueueEvent(e);
}