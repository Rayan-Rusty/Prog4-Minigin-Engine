#include "ConfirmedCommand.h"

#include "GameObject.h"
#include "SceneManager.h"
#include "Menu/MenuMarker.h"

DigDug::ConfirmedCommand::ConfirmedCommand(dae::GameObject *gameObject)
    :GameActorCommand(gameObject)
{

}

void DigDug::ConfirmedCommand::Execute()
{
    auto marker = GetGameActor()->GetComponent<MenuMarker>();
    if (!marker) return;

    int selection = marker->GetCurrentSelection();

    switch (selection)
    {
        case 0: dae::SceneManager::GetInstance().SetActiveScene(1); break;
        case 1: dae::SceneManager::GetInstance().SetActiveScene(2); break;
        case 2: dae::SceneManager::GetInstance().SetActiveScene(3); break;
        default: break;
    }
}
