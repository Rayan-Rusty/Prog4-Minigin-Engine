//
// Created by omen on 08/05/2026.
//

#ifndef MINIGIN_FYGARDEADSTATE_H
#define MINIGIN_FYGARDEADSTATE_H
#include "State.h"

namespace DigDug
{
    class FygarBehaviour;

    class FygarDeadState final : public State<FygarBehaviour>
    {
    public:
        FygarDeadState() = default;
        ~FygarDeadState() override = default;
        void Enter(FygarBehaviour& Data) override;
        std::unique_ptr<State> Update(float DeltaTime, FygarBehaviour& Data) override;
        void Exit(FygarBehaviour& Data) override;

        std::type_index GetType() const override;
    };
} // game

#endif //MINIGIN_FYGARDEADSTATE_H