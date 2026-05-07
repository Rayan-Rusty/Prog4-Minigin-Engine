//
// Created by omen on 06/05/2026.
//

#ifndef MINIGIN_POOKANORMALSTATE_H
#define MINIGIN_POOKANORMALSTATE_H
#include "PookaState.h"


class PookaNormalState : public PookaState
{
public:
    ~PookaNormalState() override;
    void Enter(Pooka& pooka) override;
    void Update(Pooka& pooka, float dt) override;
    void Exit(Pooka& pooka) override;
private:
    float m_timer = 0.0f;

};


#endif //MINIGIN_POOKANORMALSTATE_H