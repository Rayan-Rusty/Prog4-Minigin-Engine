//
// Created by omen on 02/05/2026.
//

#include "PlayerBehaviour.h"

#include "EventsIds.h"
#include "PlayerIdleState.h"


void DigDug::PlayerBehaviour::OnEvent(const dae::Event &e)
{
    if (e.id == MOVED)
    {
        m_IsMoving = e.args[2].intValue != 0;
    }
}

DigDug::PlayerBehaviour::PlayerBehaviour(dae::GameObject* owner)
    :Component(owner)
 {
     ChangeState(std::make_unique<PlayerIdleState>());
 }



void  DigDug::PlayerBehaviour::Update(float dt)
 {



    if (auto newState= m_state->Update(dt, *this))
        ChangeState(std::move(newState));
 }


void  DigDug::PlayerBehaviour::ChangeState(std::unique_ptr<State<PlayerBehaviour>> newState)
 {
     if (m_state)
         m_state->Exit(*this);

     m_state = std::move(newState);
     m_state->Enter(*this);
 }


std::type_index  DigDug::PlayerBehaviour::GetType() const
 {
     return typeid(PlayerBehaviour);
 }

bool DigDug::PlayerBehaviour::GetIsMoving() const
{
    return m_IsMoving;
}
