//
// Created by omen on 06/05/2026.
//

#ifndef MINIGIN_POOKAGHOSTSTATE_H
#define MINIGIN_POOKAGHOSTSTATE_H
#include "PookaState.h"

class PookaBehaviour;
class PookaGhostState : public PookaState
{
public:
    ~PookaGhostState() override;
    void Enter(PookaBehaviour& pooka) override;
    void Update(PookaBehaviour& pooka, float dt) override;
    void Exit(PookaBehaviour& pooka) override;
private:
    float m_timer = 0.0f;
    float m_duration = 3.0f;
};


#endif //MINIGIN_POOKAGHOSTSTATE_H