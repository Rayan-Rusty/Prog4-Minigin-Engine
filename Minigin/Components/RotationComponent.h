//
// Created by omen on 25/02/2026.
//

#ifndef MINIGIN_ROTATIONCOMPONENT_H
#define MINIGIN_ROTATIONCOMPONENT_H
#include "Component.h"
#include <glm/glm.hpp>

namespace dae
{
    class GameObject;
    class RotationComponent final : public Component
    {
    public:
        RotationComponent(GameObject* pOwner, const glm::vec3& pivot, float clockwiseDirection);


        void Update(float deltaTime) override;

        std::type_index GetType() const override;
        ~RotationComponent() = default;
        RotationComponent(const RotationComponent& other) = delete;
        RotationComponent(RotationComponent&& other) = delete;
        RotationComponent& operator=(const RotationComponent& other) = delete;
        RotationComponent& operator=(RotationComponent&& other) = delete;
    private:

        float m_clockwiseDirection;
        float m_angle{ 0.f };
        float m_distance;
        glm::vec3 m_pivot;
    };
}

#endif //MINIGIN_ROTATIONCOMPONENT_H