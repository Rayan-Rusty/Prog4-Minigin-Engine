//
// Created by omen on 09/05/2026.
//

#ifndef MINIGIN_PLAYERWALKINGSTATE_H
#define MINIGIN_PLAYERWALKINGSTATE_H
#include "MovementComponent.h"
#include "State.h"


namespace DigDug {
    class PlayerBehaviour;


    class PlayerWalkingState : public State<PlayerBehaviour>
    {
    public:
        PlayerWalkingState() = default;
        ~PlayerWalkingState() override = default;
        void Enter(PlayerBehaviour& Data) override;
        std::unique_ptr<State<PlayerBehaviour>> Update(PlayerBehaviour& Data) override;
        void Exit(PlayerBehaviour& Data) override;
    private:
        int m_Timer{0};

    };

}
#endif //MINIGIN_PLAYERWALKINGSTATE_H