
#include "Component.h"

dae::Component::Component(GameObject *owner)
    :m_owner(owner)
{
}

void dae::Component::Update(float deltaTime)
{
    (void)deltaTime; // marking it as used
}

void dae::Component::Render() const
{
}
