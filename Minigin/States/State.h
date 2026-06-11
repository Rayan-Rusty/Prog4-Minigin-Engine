//
// Created by omen on 08/05/2026.
//

#ifndef MINIGIN_STATE_H
#define MINIGIN_STATE_H
#include <memory>
#include <typeindex>
template<typename Data>
class State
{
public:
    virtual ~State() = default;

    virtual void Enter(Data& owner) = 0;
    virtual std::unique_ptr<State<Data>> Update(float DeltaTime, Data& Data) = 0;
    virtual void Exit(Data& owner) = 0;

    virtual std::type_index GetType() const = 0;
};

#endif //MINIGIN_STATE_H