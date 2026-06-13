
#ifndef MINIGIN_PLAYERWALKINGSTATE_H
#define MINIGIN_PLAYERWALKINGSTATE_H

#include "State.h"


namespace DigDug {
    class PlayerBehaviour;


    class PlayerWalkingState : public State<PlayerBehaviour>
    {
    public:


        PlayerWalkingState() = default;
        ~PlayerWalkingState() override = default;
        void Enter(PlayerBehaviour& Data) override;
        std::unique_ptr<State<PlayerBehaviour>> Update(float DeltaTime, PlayerBehaviour& Data) override;
        void Exit(PlayerBehaviour& Data) override;

        std::type_index GetType() const override;

    private:
        int m_Timer{0};
        bool m_IsMoving{false};
    };

}
#endif //MINIGIN_PLAYERWALKINGSTATE_H