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
    class MenuMarker : public dae::Component
    {
    public:
        MenuMarker(dae::GameObject* owner);

        void AddPosition(const glm::vec3& position);
        void RemovePosition(const glm::vec3& position);
        void Move(int direction);

        int GetCurrentSelection() const;

        void Update(float deltaTime) override;


        std::type_index GetType() const override;

    private:

        std::vector<glm::vec3> m_MenuPositions;
        int m_CurrentIndex;
    };
} // DigDug

#endif //MINIGIN_MENUMARKER_H