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
        void Update(FygarBehaviour& Data, float dt) override;
        void Exit(FygarBehaviour& Data) override;
    private:
    };
} // game

#endif //MINIGIN_FYGARATTACKSTATE_H