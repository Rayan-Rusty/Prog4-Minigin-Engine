
#ifndef MINIGIN_POOKAGHOSTSTATE_H
#define MINIGIN_POOKAGHOSTSTATE_H

#include "State.h"

namespace dae {
    class GameObject;
}

namespace DigDug
{
    class TilemapComponent;
    class PookaBehaviour;
    class PookaGhostState :  public State<PookaBehaviour>
    {
    public:
        ~PookaGhostState() override = default;
        void Enter(PookaBehaviour& Data) override;
        std::unique_ptr<State> Update(float DeltaTime, PookaBehaviour& Data) override;
        void Exit(PookaBehaviour& Data) override;

        std::type_index GetType() const override;

    private:
        float m_timer = 0.0f;
        float m_Speed{60.f};
        dae::GameObject* m_pPlayer{nullptr};
        DigDug::TilemapComponent* m_pTilemap{nullptr};
    };
}



#endif //MINIGIN_POOKAGHOSTSTATE_H