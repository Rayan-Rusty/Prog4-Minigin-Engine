//
// Created by omen on 15/05/2026.
//

#ifndef MINIGIN_COLLISIONCOMPONENT_H
#define MINIGIN_COLLISIONCOMPONENT_H
#include "Component.h"
#include "../DataStructs/DataStructs.h"
#include "SDL3/SDL_rect.h"

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

        SDL_FRect GetBounds() const;
        void SetBounds(const SDL_FRect& rect) { m_bounds = rect; }

        void SetEnabled(bool enabled) { m_Enabled = enabled; }
        bool IsEnabled() const { return m_Enabled; }

        bool Intersect(const CollisionComponent* other) const;



    private:
        SDL_FRect m_bounds;
        bool m_Enabled{true};
        float m_Width{0.0f};
        float m_Height{0.0f};
    };
} // dae

#endif //MINIGIN_COLLISIONCOMPONENT_H