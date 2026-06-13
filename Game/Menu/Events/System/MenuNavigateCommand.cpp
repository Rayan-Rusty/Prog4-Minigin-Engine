//
// Created by omen on 15/05/2026.
//

#include "MenuNavigateCommand.h"
#include "Scene.h"
#include "MenuMarker.h"


DigDug::MenuNavigateCommand::MenuNavigateCommand(dae::GameObject* actor , int dir)
    :GameActorCommand(actor) , m_Direction(dir)
{

}


void DigDug::MenuNavigateCommand::Execute()
{



    if (auto* marker = GetGameActor()->GetComponent<MenuMarker>()) marker->Move(m_Direction);
}
