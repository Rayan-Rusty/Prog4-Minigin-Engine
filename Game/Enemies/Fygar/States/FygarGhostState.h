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
        std::unique_ptr<State> Update(float DeltaTime, FygarBehaviour& Data) override;
        void Exit(FygarBehaviour& Data) override;

        std::type_index GetType() const override;

    private:
    };
} // game

#endif //MINIGIN_FYGARGHOSTSTATE_H