#ifndef MINIGIN_PLAYERMOVEMENT_H
#define MINIGIN_PLAYERMOVEMENT_H
#include "Component.h"
#include <glm/glm.hpp>


namespace DigDug {
    class TilemapComponent;

    class PlayerMovement final : public dae::Component
    {
    public:
        explicit  PlayerMovement(dae::GameObject* gameObject);
        ~PlayerMovement() override = default;

        void Update(float deltaTime) override;
        std::type_index GetType() const override;
        bool IsMoving() const{ return m_IsMoving; }
        void SetDirection(const glm::ivec2& dir);
        glm::ivec2 GetDirection() const { return m_InputDir; }

        PlayerMovement(const PlayerMovement& other) = delete;
        PlayerMovement(PlayerMovement&& other) = delete;
        PlayerMovement& operator=(const PlayerMovement& other) = delete;
        PlayerMovement& operator=(PlayerMovement&& other) = delete;

    private:

        void FlipDirection();

        void BeginMoveTo(const glm::ivec2& nextGrid);

        bool m_IsMoving{false};

        TilemapComponent* m_pTilemap{nullptr};
        float m_Speed{100.f};
        glm::ivec2 m_InputDir{0, 0};
        glm::vec3 m_TargetPos{0.0f, 0.0f, 0.0f};

    };
} // DigDug

#endif //MINIGIN_PLAYERMOVEMENT_H