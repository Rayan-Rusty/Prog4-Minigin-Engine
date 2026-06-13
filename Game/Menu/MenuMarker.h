//
// Created by omen on 15/05/2026.
//

#ifndef MINIGIN_MENUMARKER_H
#define MINIGIN_MENUMARKER_H
#include "CollisionComponent.h"

namespace dae {
    class GameObject;
}
namespace DigDug
{
    class MenuMarker final : public dae::Component
    {
    public:
        explicit MenuMarker(dae::GameObject* owner);
        ~MenuMarker() override = default;
        void AddPosition(const glm::vec3& position);
        void RemovePosition(const glm::vec3& position);
        void Move(int direction);
        int GetcurrentSelection() const{return m_CurrentIndex;};

        int GetCurrentSelection() const;

        void Update(float deltaTime) override;


        std::type_index GetType() const override;
        MenuMarker(const MenuMarker& other) = delete;
        MenuMarker(MenuMarker&& other) = delete;
        MenuMarker& operator=(const MenuMarker& other) = delete;
        MenuMarker& operator=(MenuMarker&& other) = delete;
    private:

        std::vector<glm::vec3> m_MenuPositions;
        int m_CurrentIndex{0};
        float m_MoveSpeed{300.f};
        glm::vec3 m_TargetPosition{};
    };
} // DigDug

#endif //MINIGIN_MENUMARKER_H