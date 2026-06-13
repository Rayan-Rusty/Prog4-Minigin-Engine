
#include "MenuNavigateSystem.h"
#include "MenuMarker.h"
#include "GameObject.h"
#include "EventsIds.h"



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
