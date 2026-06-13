

#include "FygarBehaviour.h"

#include "FygarAttackState.h"

#include "FygarGhostState.h"
#include "FygarInflatedState.h"
#include "FygarNormalState.h"
#include "SceneManager.h"
#include "ScoreComponent.h"
#include "GameLayers.h"

#include "FygarMovement.h"


DigDug::FygarBehaviour::FygarBehaviour(dae::GameObject *owner)
    : Component(owner)
{
    auto* scene = dae::SceneManager::GetInstance().GetActiveScene();

    auto pumpObjs = scene->GetObjectByTag(static_cast<int>(GameTag::Pump));
    if (!pumpObjs.empty())
    {
        m_pumpActor = pumpObjs[0]->GetActor();
        m_pumpActor->AddObserver(this);
    }

    auto* movement = GetOwner()->GetComponent<FygarMovement>();
    if (movement)
    {
        m_movementActor = movement->GetOwner()->GetActor();
        m_movementActor->AddObserver(this);
    }


    auto scoreObjs = scene->GetObjectByTag(static_cast<int>(GameTag::UI));
    if (!scoreObjs.empty())
    {
        if (auto* scoreComp = scoreObjs[0]->GetComponent<ScoreComponent>())
            GetOwner()->GetActor()->AddObserver(scoreComp);
    }

    ChangeState(std::make_unique<FygarNormalState>());
}

DigDug::FygarBehaviour::~FygarBehaviour() {
}


void DigDug::FygarBehaviour::Notify(dae::IObserver::Event event, dae::GameActor *)
{
    if (event == dae::IObserver::Event::EnemyHitWall)
    {
        if (m_dist(m_Rng) < m_GhostChance)
            ChangeState(std::make_unique<FygarGhostState>());
    }
    if (event == dae::IObserver::Event::PumpHitEnemy)
    {
        ChangeState(std::make_unique<FygarInflatedState>());
    }
}

void DigDug::FygarBehaviour::Update(float dt)
{
    if (m_state)
    {
        auto newState = m_state->Update(dt, *this);
        if (newState)
            ChangeState(std::move(newState));
    }
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
    return std::type_index(typeid(FygarBehaviour));
}

State<DigDug::FygarBehaviour> * DigDug::FygarBehaviour::GetState() const
{
    return m_state.get();
}
