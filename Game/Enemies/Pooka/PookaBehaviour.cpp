//
// Created by omen on 06/05/2026.
//

#include "PookaBehaviour.h"

#include "PookaGhostState.h"
#include "PookaNormalState.h"
#include "Movement/PookaMovement.h"


DigDug::PookaBehaviour::PookaBehaviour(dae::GameObject* owner)
    :Component(owner)
{

    auto* movement = GetOwner()->GetComponent<PookaMovement>();
    if (movement)
        movement->GetOwner()->GetActor()->AddObserver(this);

    ChangeState(std::make_unique<PookaNormalState>());
}


void DigDug::PookaBehaviour::Notify(Event event, dae::GameActor *)
{
    if (event == dae::IObserver::Event::EnemyHitWall)
    {
        ChangeState(std::make_unique<PookaGhostState>());
    }
}

void  DigDug::PookaBehaviour::Update(float dt )
{
     auto newState = m_state->Update(dt, *this);
     if (newState)
         ChangeState(std::move(newState));
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