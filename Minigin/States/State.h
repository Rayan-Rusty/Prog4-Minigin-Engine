//
// Created by omen on 08/05/2026.
//

#ifndef MINIGIN_STATE_H
#define MINIGIN_STATE_H
#include <memory>

template<typename Data>
class State
{
public:
    virtual ~State() = default;

    virtual void Enter(Data& owner) = 0;
    virtual std::unique_ptr<State<Data>> Update(Data& Data) = 0;
    virtual void Exit(Data& owner) = 0;
};

#endif //MINIGIN_STATE_H