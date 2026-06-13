#include "PumpBehaviour.h"

#include "EventsIds.h"
#include "State/PumpIdleState.h"



DigDug::PumpBehaviour::PumpBehaviour(dae::GameObject* owner)
    :Component(owner)
{
    ChangeState(std::make_unique<PumpIdleState>());
}

void DigDug::PumpBehaviour::OnEvent(const dae::Event &e)
{
    if (e.id == MOVED)
    {
        m_Dir.x = e.args[0].intValue;
        m_Dir.y = e.args[1].intValue;
    }
}



void  DigDug::PumpBehaviour::Update(float dt)
{

    if (auto newState= m_state->Update(dt, *this))
        ChangeState(std::move(newState));
}


void  DigDug::PumpBehaviour::ChangeState(std::unique_ptr<State<PumpBehaviour>> newState)
{
    if (m_state)
        m_state->Exit(*this);

    m_state = std::move(newState);
    m_state->Enter(*this);
}


std::type_index  DigDug::PumpBehaviour::GetType() const
{
    return typeid(PumpBehaviour);
}