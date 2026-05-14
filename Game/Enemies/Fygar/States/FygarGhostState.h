//
// Created by omen on 08/05/2026.
//

#ifndef MINIGIN_FYGARGHOSTSTATE_H
#define MINIGIN_FYGARGHOSTSTATE_H
#include "State.h"



namespace DigDug
{
    class FygarBehaviour;
    class FygarGhostState : public State<FygarBehaviour>
    {
    public:
        ~FygarGhostState() override = default;
        void Enter(FygarBehaviour& Data) override;
        void Update(FygarBehaviour& Data, float dt) override;
        void Exit(FygarBehaviour& Data) override;
    private:
    };
} // game

#endif //MINIGIN_FYGARGHOSTSTATE_H