//
// Created by omen on 11/03/2026.
//

#ifndef MINIGIN_MOVEMENTCOMPONENT_H
#define MINIGIN_MOVEMENTCOMPONENT_H
#include <typeindex>

#include "Component.h"
#include <glm/glm.hpp>

namespace dae
{
    class MovementComponent final : public Component
    {
    public:
        MovementComponent(GameObject* owner , float speed, bool gravity = false);

        void Update(float deltaTime) override;
        std::type_index GetType() const override;
        void Move(const glm::vec3& direction);


        MovementComponent(const MovementComponent& other) = delete;
        MovementComponent(MovementComponent&& other) = delete;
        MovementComponent& operator=(const MovementComponent& other) = delete;
        MovementComponent& operator=(MovementComponent&& other) = delete;
    private:
        float m_Speed{0.f};
        bool m_Gravity{false};
        glm::vec3 m_velocity{0,0,0};

    };
}



#endif //MINIGIN_MOVEMENTCOMPONENT_H