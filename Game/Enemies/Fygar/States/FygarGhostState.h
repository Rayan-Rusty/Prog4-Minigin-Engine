//
// Created by omen on 08/05/2026.
//

#ifndef MINIGIN_FYGARGHOSTSTATE_H
#define MINIGIN_FYGARGHOSTSTATE_H
#include "State.h"


namespace dae
{
    class GameObject;
}

namespace DigDug
{
    class TilemapComponent;
    class FygarBehaviour;

    class FygarGhostState final : public State<FygarBehaviour>
    {
    public:
        FygarGhostState() = default;
        ~FygarGhostState() override = default;
        void Enter(FygarBehaviour& Data) override;
        std::unique_ptr<State> Update(float DeltaTime, FygarBehaviour& Data) override;
        void Exit(FygarBehaviour& Data) override;

        std::type_index GetType() const override;

    private:
        float m_timer = 0.0f;
        float m_Speed{60.f};
        dae::GameObject* m_pPlayer{nullptr};
        DigDug::TilemapComponent* m_pTilemap{nullptr};
    };
} // game

#endif //MINIGIN_FYGARGHOSTSTATE_H