//
// Created by omen on 06/05/2026.
//

#ifndef MINIGIN_POOKANORMALSTATE_H
#define MINIGIN_POOKANORMALSTATE_H
#include "PookaState.h"


class PookaNormalState : public PookaState
{
public:
    void Enter(Pooka& pooka) override;
    void Update(Pooka& pooka) override;
    void Exit(Pooka& pooka) override;
private:
};


#endif //MINIGIN_POOKANORMALSTATE_H