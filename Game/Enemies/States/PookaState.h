//
// Created by omen on 06/05/2026.
//

#ifndef MINIGIN_POOKASTATE_H
#define MINIGIN_POOKASTATE_H

class Pooka;
class PookaState
{
public:
    virtual ~PookaState() = default;

    virtual void Enter(Pooka& pooka);
    virtual void Update(Pooka& pooka , float dt) = 0;
    virtual void Exit(Pooka& pooka);

};


#endif //MINIGIN_POOKASTATE_H