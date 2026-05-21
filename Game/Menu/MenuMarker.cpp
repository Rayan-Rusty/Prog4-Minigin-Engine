//
// Created by omen on 15/05/2026.
//

#include "MenuMarker.h"

#include "GameObject.h"


DigDug::MenuMarker::MenuMarker(dae::GameObject *owner)
    :Component(owner)
{
}

void DigDug::MenuMarker::AddPosition(const glm::vec3 &position)
{
    m_MenuPositions.emplace_back(position);
}
void DigDug::MenuMarker::RemovePosition(const glm::vec3 &position)
{
    m_MenuPositions.erase(
        std::remove(
            m_MenuPositions.begin(),
            m_MenuPositions.end(),
            position),
        m_MenuPositions.end()
    );
}


void DigDug::MenuMarker::Move(int direction)
{
    if (m_MenuPositions.empty())
        return;

    m_CurrentIndex += direction;

    if (m_CurrentIndex < 0)
        m_CurrentIndex = static_cast<int>(m_MenuPositions.size()) - 1;

    if (m_CurrentIndex >= static_cast<int>(m_MenuPositions.size()))
        m_CurrentIndex = 0;

    GetOwner()->GetTransform().SetWorldPosition(
        m_MenuPositions[m_CurrentIndex]
    );
}

void DigDug::MenuMarker::Update(float)
{

}



int DigDug::MenuMarker::GetCurrentSelection() const {
    return m_CurrentIndex;
}

std::type_index DigDug::MenuMarker::GetType() const {
    return typeid(MenuMarker);
}
