//
// Created by omen on 06/05/2026.
//

#include "PookaBehaviour.h"

#include "States/PookaNormalState.h"
#include "States/PookaState.h"

PookaBehaviour::PookaBehaviour(dae::GameObject* owner)
    :Component(owner)
{
    ChangeState(std::make_unique<PookaNormalState>());
}

PookaBehaviour::~PookaBehaviour() {

}


void PookaBehaviour::Update(float dt)
{
    if (m_state)
        m_state->Update(*this , dt);
}


void PookaBehaviour::ChangeState(std::unique_ptr<PookaState> newState)
{
    if (m_state)
        m_state->Exit(*this);

    m_state = std::move(newState);
    m_state->Enter(*this);
}


std::type_index PookaBehaviour::GetType() const
{
    return typeid(PookaBehaviour);
}