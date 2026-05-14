//
// Created by omen on 08/05/2026.
//

#ifndef MINIGIN_FYGARDEADSTATE_H
#define MINIGIN_FYGARDEADSTATE_H
#include "State.h"

namespace DigDug
{
    class FygarBehaviour;

    class FygarDeadState: public State<FygarBehaviour>
    {
    public:
        ~FygarDeadState() override = default;
        void Enter(FygarBehaviour& Data) override;
        void Update(FygarBehaviour& Data, float dt) override;
        void Exit(FygarBehaviour& Data) override;
    };
} // game

#endif //MINIGIN_FYGARDEADSTATE_H