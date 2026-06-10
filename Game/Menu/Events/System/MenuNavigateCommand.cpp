//
// Created by omen on 15/05/2026.
//

#include "MenuNavigateCommand.h"
#include "Scene.h"
#include "Menu/MenuMarker.h"


DigDug::MenuNavigateCommand::MenuNavigateCommand(dae::GameObject* actor , int dir)
    :GameActorCommand(actor) , m_Direction(dir)
{

}

DigDug::MenuNavigateCommand::~MenuNavigateCommand() {

}

void DigDug::MenuNavigateCommand::Execute()
{

    auto* marker = GetGameActor()->GetComponent<MenuMarker>();

    if (marker) marker->Move(m_Direction);
}
