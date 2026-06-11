//
// Created by omen on 08/05/2026.
//

#ifndef MINIGIN_FYGARATTACKSTATE_H
#define MINIGIN_FYGARATTACKSTATE_H
#include "State.h"



namespace DigDug
{
    class FygarBehaviour;
    class FygarAttackState : public State<FygarBehaviour>
    {
    public:
        ~FygarAttackState() override = default;
        void Enter(FygarBehaviour& Data) override;
        std::unique_ptr<State<FygarBehaviour>> Update(float DeltaTime, FygarBehaviour& Data) override;
        void Exit(FygarBehaviour& Data) override;

        std::type_index GetType() const override;

    private:
    };
} // game

#endif //MINIGIN_FYGARATTACKSTATE_H