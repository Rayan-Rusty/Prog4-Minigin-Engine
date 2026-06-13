//
// Created by omen on 25/02/2026.
//

#include "../RotationComponent.h"
#include "GameObject.h"
//TODO REMOVE PIVOT , WRAP , ANGLE

dae::RotationComponent::RotationComponent(GameObject* pOwner, float clockwiseDirection)
    : Component(pOwner), m_clockwiseDirection(clockwiseDirection)
{
    //TODO How does it know to rotate around an object
    m_distance = static_cast<float>(glm::length((GetOwner()->GetTransform().GetLocalPosition() )));
}

void dae::RotationComponent::Update(float deltaTime)
{

    //increase angle
    m_angle += deltaTime * m_clockwiseDirection;

    glm::vec2 angles {cos(m_angle) * m_distance , sin(m_angle) * m_distance};

    glm::vec3 newPos{ glm::vec3{angles , 0 } };
    GetOwner()->GetTransform().SetLocalPosition(newPos);
}

std::type_index dae::RotationComponent::GetType() const
{
    return typeid(RotationComponent);
}