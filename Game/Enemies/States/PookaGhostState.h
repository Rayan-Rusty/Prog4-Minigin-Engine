//
// Created by omen on 06/05/2026.
//

#ifndef MINIGIN_POOKAGHOSTSTATE_H
#define MINIGIN_POOKAGHOSTSTATE_H
#include "PookaState.h"

class Pooka;
class PookaGhostState : public PookaState
{
    void Enter(Pooka& pooka) override;
    void Update(Pooka& pooka) override;
    void Exit(Pooka& pooka) override;
};


#endif //MINIGIN_POOKAGHOSTSTATE_H