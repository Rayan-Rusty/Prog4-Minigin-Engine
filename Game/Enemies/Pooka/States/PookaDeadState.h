//
// Created by omen on 08/05/2026.
//

#ifndef MINIGIN_POOKADEADSTATE_H
#define MINIGIN_POOKADEADSTATE_H
#include "State.h"

namespace game
{
    class PookaBehaviour;
    class PookaDeadState : public State<PookaBehaviour>
    {
    public:
        ~PookaDeadState() override = default;
        void Enter(PookaBehaviour& Data) override;
        void Update(PookaBehaviour& Data, float dt) override;
        void Exit(PookaBehaviour& Data) override;
    private:
        float m_timer{0.f};
    };
}



#endif //MINIGIN_POOKADEADSTATE_H