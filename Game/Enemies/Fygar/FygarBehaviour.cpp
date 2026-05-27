//
// Created by omen on 08/05/2026.
//

#include "FygarBehaviour.h"

#include "FygarAttackState.h"



DigDug::FygarBehaviour::FygarBehaviour(dae::GameObject *owner)
    : Component(owner)
{
    ChangeState(std::make_unique<FygarAttackState>());
}


void DigDug::FygarBehaviour::Update(float)
{
    //if (m_state)
    //     m_state->Update(*this , dt);
}


void DigDug::FygarBehaviour::ChangeState(std::unique_ptr<State<FygarBehaviour> > newState)
{
    if (m_state)
        m_state->Exit(*this);

    m_state = std::move(newState);
    m_state->Enter(*this);
}


std::type_index DigDug::FygarBehaviour::GetType() const
{
    return typeid(FygarBehaviour);
}
