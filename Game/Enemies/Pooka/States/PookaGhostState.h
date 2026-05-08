//
// Created by omen on 06/05/2026.
//

#ifndef MINIGIN_POOKAGHOSTSTATE_H
#define MINIGIN_POOKAGHOSTSTATE_H

#include "State.h"
namespace game
{
    class PookaBehaviour;
    class PookaGhostState :  public State<PookaBehaviour>
    {
    public:
        ~PookaGhostState() override = default;
        void Enter(PookaBehaviour& Data) override;
        void Update(PookaBehaviour& Data, float dt) override;
        void Exit(PookaBehaviour& Data) override;
    private:
        float m_timer = 0.0f;
        float m_duration = 3.0f;
    };
}



#endif //MINIGIN_POOKAGHOSTSTATE_H