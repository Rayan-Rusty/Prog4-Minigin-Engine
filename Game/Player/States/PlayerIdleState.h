//
// Created by omen on 09/05/2026.
//

#ifndef MINIGIN_PLAYERIDLESTATE_H
#define MINIGIN_PLAYERIDLESTATE_H
#include "State.h"

namespace DigDug
{
    class PlayerBehaviour;

    class PlayerIdleState : public State<PlayerBehaviour>
    {
    public:
        PlayerIdleState()  = default;
        ~PlayerIdleState() override = default;
        void Enter(PlayerBehaviour& Data) override;
        void Update(PlayerBehaviour& Data, float dt) override;
        void Exit(PlayerBehaviour& Data) override;
    private:
        float m_Timer { 0.0f};

    };
}



#endif //MINIGIN_PLAYERIDLESTATE_H