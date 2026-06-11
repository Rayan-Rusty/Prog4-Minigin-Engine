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
        std::unique_ptr<State> Update(float DeltaTime, PlayerBehaviour& Data) override;
        void Exit(PlayerBehaviour& Data) override;

        std::type_index GetType() const override;

    private:
        float m_Timer { 0.0f};

    };
}



#endif //MINIGIN_PLAYERIDLESTATE_H