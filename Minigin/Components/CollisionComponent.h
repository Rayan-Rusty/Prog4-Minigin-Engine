//
// Created by omen on 15/05/2026.
//

#ifndef MINIGIN_COLLISIONCOMPONENT_H
#define MINIGIN_COLLISIONCOMPONENT_H
#include "Component.h"
#include "DataStructs.h"

#include <typeindex>

namespace dae
{

    class CollisionComponent : public Component
    {
    public:
        CollisionComponent(GameObject* owner);
        ~CollisionComponent();

        void Update(float deltaTime) override;
        void Render() const override;
        std::type_index GetType() const override;

        //dae::Rect GetBounds() const;
        //void SetBounds(const Rect& rect) { m_bounds = rect; }

        void SetEnabled(bool enabled) { m_Enabled = enabled; }
        bool IsEnabled() const { return m_Enabled; }

        bool Intersect(const CollisionComponent* other) const;



    private:
        //Rectf m_bounds;
        bool m_Enabled{true};
        float m_Width{0.0f};
        float m_Height{0.0f};
        glm::vec2 m_Offset{0, 0};
    };
} // dae

#endif //MINIGIN_COLLISIONCOMPONENT_H