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
    void Enter(PookaBehaviour& pooka) override;
    void Update(PookaBehaviour& pooka, float dt) override;
    void Exit(PookaBehaviour& pooka) override;
private:
    float m_timer = 0.0f;

};


#endif //MINIGIN_POOKANORMALSTATE_H