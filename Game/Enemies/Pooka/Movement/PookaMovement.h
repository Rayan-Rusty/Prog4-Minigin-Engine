#ifndef MINIGIN_POOKAMOVEMENT_H
#define MINIGIN_POOKAMOVEMENT_H
#include "Component.h"
#include "EnemyTraits.h"
#include "TilemapComponent.h"
#include "glm/vec2.hpp"
namespace dae {
    class GameObject;
}
namespace DigDug
{
    class PookaMovement final : public dae::Component
    {
    public:
        explicit PookaMovement(dae::GameObject* parent);
        ~PookaMovement() override = default;

        void Update(float deltaTime) override;
        std::type_index GetType() const override;
        void Move(float dt);
        void SetSpeed(float speed);

        PookaMovement(const PookaMovement& other) = delete;
        PookaMovement(PookaMovement&& other) = delete;
        PookaMovement& operator=(const PookaMovement& other) = delete;
        PookaMovement& operator=(PookaMovement&& other) = delete;
    private:
        float m_Speed{80.f};
        glm::ivec2 m_lastGrid{ -1, -1 };
        glm::vec2 m_Dir{1.f,0.f};
        bool m_FacingLeft{false};
        bool m_IsGhost{false};
        void ChangeDirection(glm::ivec2 wallGrid);

        TilemapComponent* m_pSceneTileMap{nullptr};
        dae::GameObject* m_pPlayer{nullptr};



    };
} // DigDug

#endif //MINIGIN_POOKAMOVEMENT_H