//
// Created by omen on 06/05/2026.
//

#include "PookaBehaviour.h"

#include "PookaNormalState.h"


 DigDug::PookaBehaviour::PookaBehaviour(dae::GameObject* owner)
    :Component(owner)
{
    ChangeState(std::make_unique<PookaNormalState>());
}



void  DigDug::PookaBehaviour::Update(float dt)
{
    if (m_state)
        m_state->Update(*this , dt);
}


void  DigDug::PookaBehaviour::ChangeState(std::unique_ptr<State<PookaBehaviour>> newState)
{
    if (m_state)
        m_state->Exit(*this);

    m_state = std::move(newState);
    m_state->Enter(*this);
}


std::type_index  DigDug::PookaBehaviour::GetType() const
{
    return typeid(PookaBehaviour);
}