//
// Created by omen on 15/05/2026.
//

#include "MenuNavigateSystem.h"
#include "Menu/MenuMarker.h"
#include "GameObject.h"
#include "EventsIds.h"
#include "MenuNavigateCommand.h"


DigDug::MenuNavigateSystem::MenuNavigateSystem(dae::GameObject* Object)
    : m_MenuObject(Object)
{
}

DigDug::MenuNavigateSystem::~MenuNavigateSystem()
{
}

void DigDug::MenuNavigateSystem::OnEvent(const dae::Event &e)
{
    if (e.id != MENU_NAVIGATE)
        return;

    auto dir = (e.args[0].intValue);
    auto marker = m_MenuObject->GetComponent<MenuMarker>();

    marker->Move(dir);

}
