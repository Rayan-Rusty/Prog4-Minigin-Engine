//
// Created by omen on 08/05/2026.
//

#ifndef MINIGIN_POOKAINFLATEDSTATE_H
#define MINIGIN_POOKAINFLATEDSTATE_H
#include "State.h"

namespace DigDug
{
    class PookaBehaviour;

    class PookaInflatedState: public State<PookaBehaviour>
    {
    public:
        ~PookaInflatedState() override = default;
        void Enter(PookaBehaviour& Data) override;
        void Update(PookaBehaviour& Data, float dt) override;
        void Exit(PookaBehaviour& Data) override;
    private:
        float m_timer{0.f};
    };
} // game

#endif //MINIGIN_POOKAINFLATEDSTATE_H