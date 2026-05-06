//
// Created by omen on 06/05/2026.
//

#ifndef MINIGIN_POOKAGHOSTSTATE_H
#define MINIGIN_POOKAGHOSTSTATE_H
#include "PookaState.h"

class Pooka;
class PookaGhostState : public PookaState
{
public:
    ~PookaGhostState() override;
    void Enter(Pooka& pooka) override;
    void Update(Pooka& pooka, float dt) override;
    void Exit(Pooka& pooka) override;
private:
    float m_timer = 0.0f;
    float m_duration = 3.0f;
};


#endif //MINIGIN_POOKAGHOSTSTATE_H