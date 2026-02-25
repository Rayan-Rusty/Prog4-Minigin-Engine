//
// Created by omen on 25/02/2026.
//

#include "RotationComponent.h"
#include "GameObject.h"

dae::RotationComponent::RotationComponent(GameObject* pOwner, const glm::vec3& pivot, float clockwiseDirection)
    : Component(pOwner)
    , m_pivot(pivot), m_clockwiseDirection(clockwiseDirection)
{
    m_distance = static_cast<float>(glm::length((GetOwner()->GetLocalPosition() - m_pivot)));
}

void dae::RotationComponent::Update(float deltaTime)
{

    //increase angle
    m_angle += deltaTime * m_clockwiseDirection;

    glm::vec2 angles {cos(m_angle) * m_distance , sin(m_angle) * m_distance};

    glm::vec3 newPos{ m_pivot + glm::vec3{angles , 0 } };
    GetOwner()->SetLocalPosition(newPos);
}

std::type_index dae::RotationComponent::GetType() const
{
    return typeid(RotationComponent);
}