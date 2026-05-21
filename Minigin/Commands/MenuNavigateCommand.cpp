//
// Created by omen on 15/05/2026.
//

#include "MenuNavigateCommand.h"

#include "EventsIds.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "Menu/MenuMarker.h"


dae::MenuNavigateCommand::MenuNavigateCommand(GameObject* actor , int dir)
    :GameActorCommand(actor) , m_Direction(dir)
{

}

dae::MenuNavigateCommand::~MenuNavigateCommand() {

}

void dae::MenuNavigateCommand::Execute()
{

    Event e(MENU_NAVIGATE);


    e.nbArgs = 1;
    e.args[0].intValue = (m_Direction);

    SceneManager::GetInstance().GetEventBus().QueueEvent(e);
}
