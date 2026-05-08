//
// Created by omen on 06/05/2026.
//

#include "PookaBehaviour.h"

#include "States/PookaNormalState.h"


 game::PookaBehaviour::PookaBehaviour(dae::GameObject* owner)
    :Component(owner)
{
    ChangeState(std::make_unique<PookaNormalState>());
}



void  game::PookaBehaviour::Update(float dt)
{
    if (m_state)
        m_state->Update(*this , dt);
}


void  game::PookaBehaviour::ChangeState(std::unique_ptr<State<PookaBehaviour>> newState)
{
    if (m_state)
        m_state->Exit(*this);

    m_state = std::move(newState);
    m_state->Enter(*this);
}


std::type_index  game::PookaBehaviour::GetType() const
{
    return typeid(PookaBehaviour);
}