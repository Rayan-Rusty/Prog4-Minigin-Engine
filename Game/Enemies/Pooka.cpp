//
// Created by omen on 06/05/2026.
//

#include "Pooka.h"

#include "States/PookaNormalState.h"
#include "States/PookaState.h"

Pooka::Pooka(dae::GameObject* owner)
    :Component(owner)
{
    ChangeState(std::make_unique<PookaNormalState>());
}

Pooka::~Pooka() {

}


void Pooka::Update(float dt)
{
    if (m_state)
        m_state->Update(*this , dt);
}


void Pooka::ChangeState(std::unique_ptr<PookaState> newState)
{
    if (m_state)
        m_state->Exit(*this);

    m_state = std::move(newState);
    m_state->Enter(*this);
}


std::type_index Pooka::GetType() const
{
    return typeid(Pooka);
}