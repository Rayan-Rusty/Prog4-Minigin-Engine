//
// Created by omen on 11/03/2026.
//

#include "MovementComponent.h"

#include "GameObject.h"


dae::MovementComponent::MovementComponent(GameObject *owner, float speed, bool gravity)
    : Component(owner) , m_Speed(speed) , m_Gravity(gravity)
{

}


void dae::MovementComponent::Update(float deltaTime)
{
    auto pos {GetOwner()->GetTransform().GetLocalPosition()};
    pos += m_velocity * deltaTime;

    if (m_Gravity)
        pos.y += m_Gravity * deltaTime;

    GetOwner()->GetTransform().SetLocalPosition(pos);

    m_velocity = glm::vec3{0,0,0};

}


void dae::MovementComponent::Move(const glm::vec3 &direction)
{
    m_velocity += direction * m_Speed;
}


std::type_index dae::MovementComponent::GetType() const
{
    return typeid(MovementComponent);
}
