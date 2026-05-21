//
// Created by omen on 11/03/2026.
//

#include "MovementComponent.h"

#include "../GameObject/GameObject.h"


dae::MovementComponent::MovementComponent(GameObject *owner, float speed, bool gravity)
    : Component(owner) , m_Speed(speed) , m_Gravity(gravity)
{

}


void dae::MovementComponent::Update(float deltaTime)
{


    auto pos = GetOwner()->GetTransform().GetLocalPosition();
    pos += m_Direction * m_Speed * deltaTime;

    if (m_Gravity)
        pos.y -= m_Speed * deltaTime;

    GetOwner()->GetTransform().SetLocalPosition(pos);

    m_IsMoving = glm::length(m_Direction) > 0.0f;
    m_Direction = glm::vec3{0.0f, 0.0f, 0.0f};
}


void dae::MovementComponent::Move(const glm::vec3 &direction)
{
    m_Direction = direction;

}

bool dae::MovementComponent::IsMoving() const
{
    return m_IsMoving;
}

std::type_index dae::MovementComponent::GetType() const
{
    return typeid(MovementComponent);
}
