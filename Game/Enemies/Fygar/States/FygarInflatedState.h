//
// Created by omen on 08/05/2026.
//

#ifndef MINIGIN_FYGARINFLATEDSTATE_H
#define MINIGIN_FYGARINFLATEDSTATE_H
#include "State.h"

namespace DigDug {
    class FygarBehaviour;

    class FygarInflatedState final: public State<FygarBehaviour>
    {
    public:
        FygarInflatedState() = default;
        ~FygarInflatedState() override = default;
        void Enter(FygarBehaviour& Data) override;
        std::unique_ptr<State> Update(float DeltaTime, FygarBehaviour& Data) override;
        void Exit(FygarBehaviour& Data) override;

        std::type_index GetType() const override;

    private:
        float m_timer{0.f};
        float m_DeflateTime{0.8f};
    };
} // game

#endif //MINIGIN_FYGARINFLATEDSTATE_H