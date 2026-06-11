//
// Created by omen on 08/05/2026.
//

#ifndef MINIGIN_FYGARNORMALSTATE_H
#define MINIGIN_FYGARNORMALSTATE_H
#include "State.h"


namespace DigDug
{
    class FygarBehaviour;
    class FygarNormalState  : public State<FygarBehaviour>
    {
    public:
        FygarNormalState() = default;
        ~FygarNormalState() override = default;
        void Enter(FygarBehaviour& Data) override;
        std::unique_ptr<State> Update(float DeltaTime, FygarBehaviour& Data) override;
        void Exit(FygarBehaviour& Data) override;
    private:
    };
} // game

#endif //MINIGIN_FYGARNORMALSTATE_H