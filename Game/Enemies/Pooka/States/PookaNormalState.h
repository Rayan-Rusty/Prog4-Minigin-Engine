//
// Created by omen on 06/05/2026.
//

#ifndef MINIGIN_POOKANORMALSTATE_H
#define MINIGIN_POOKANORMALSTATE_H

#include "State.h"
namespace DigDug
{
    class PookaBehaviour;
    class PookaNormalState : public State<PookaBehaviour>
    {
    public:
        ~PookaNormalState() override = default;
        void Enter(PookaBehaviour& Data) override;
        void Update(PookaBehaviour& Data, float dt) override;
        void Exit(PookaBehaviour& Data) override;
    private:
        float m_timer = 0.0f;

    };

}


#endif //MINIGIN_POOKANORMALSTATE_H