//
// Created by omen on 06/05/2026.
//

#ifndef MINIGIN_POOKASTATE_H
#define MINIGIN_POOKASTATE_H

class PookaBehaviour;
class PookaState
{
public:
    virtual ~PookaState() = default;

    virtual void Enter(PookaBehaviour& pooka) = 0;
    virtual void Update(PookaBehaviour& pooka , float dt) = 0;
    virtual void Exit(PookaBehaviour& pooka) = 0;

};


#endif //MINIGIN_POOKASTATE_H