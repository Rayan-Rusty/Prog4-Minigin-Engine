//
// Created by omen on 02/05/2026.
//

#include "PlayerBehaviour.h"

#include "PlayerIdleState.h"


DigDug::PlayerBehaviour::PlayerBehaviour(dae::GameObject* owner)
    :Component(owner)
 {
     ChangeState(std::make_unique<PlayerIdleState>());
 }



void  DigDug::PlayerBehaviour::Update(float )
 {

    if (auto newState= m_state->Update(*this))
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