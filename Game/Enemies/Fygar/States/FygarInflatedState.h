//
// Created by omen on 08/05/2026.
//

#ifndef MINIGIN_FYGARINFLATEDSTATE_H
#define MINIGIN_FYGARINFLATEDSTATE_H
#include "State.h"

namespace game {
    class FygarBehaviour;

    class FygarInflatedState: public State<FygarBehaviour>
    {
    public:
        ~FygarInflatedState() override = default;
        void Enter(FygarBehaviour& Data) override;
        void Update(FygarBehaviour& Data, float dt) override;
        void Exit(FygarBehaviour& Data) override;
    private:
    };
} // game

#endif //MINIGIN_FYGARINFLATEDSTATE_H